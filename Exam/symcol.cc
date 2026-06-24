#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include "root.h"
#include "evd.h"

// Made with chat bot

// Secular function and derivative for one lambda
static void secular_one(const std::vector<double>& d,
                         const std::vector<double>& u,
                         int p,
                         double lambda,
                         double& f,
                         double& df)
{
    int n = (int)d.size();
    double S = 0.0, dS = 0.0;
    for (int k = 0; k < n; ++k) {
        if (k == p) continue;
        double den  = d[k] - lambda;
        double den2 = den * den;
        S  += u[k]*u[k] / den;
        dS += u[k]*u[k] / den2;
    }
    f  = d[p] + 2.0*u[p] - lambda - S;
    df = -1.0 + dS;
}

static pp::vector compute_eigenvector(const std::vector<double>& d,
                                       const std::vector<double>& u,
                                       int p,
                                       double lambda)
{
    int n = (int)d.size();
    pp::vector v(n);

    // Check if lambda == d[k] for some k != p (u[k]==0 case)
    for (int k = 0; k < n; ++k) {
        if (k == p) continue;
        if (std::abs(d[k] - lambda) < 1e-12) {
            pp::vector ek(n);
            ek[k] = 1.0;
            return ek;
        }
    }

    // Set alpha = v_p = 1 (free scaling before normalization)
    // v_k = -u_k / (d_k - lambda)  for k != p
    for (int k = 0; k < n; ++k) {
        if (k == p) continue;
        double den = d[k] - lambda;
        if (std::abs(den) < 1e-12)
            v[k] = 0.0;   // u[k] should be ~0 here anyway
        else
            v[k] = -u[k] / den;
    }

    // beta = u^T v = sum_{k!=p} u_k * v_k + u_p * v_p
    // with v_p = 1:
    double beta = u[p];   // u_p * alpha = u_p * 1
    for (int k = 0; k < n; ++k) {
        if (k == p) continue;
        beta += u[k] * v[k];
    }

    // v_p = -(u_p * alpha + beta) / (d_p - lambda)
    double denp = d[p] - lambda;
    if (std::abs(denp) < 1e-12)
        v[p] = 1.0;
    else
        v[p] = -(u[p] + beta) / denp;

    // Normalize
    double norm = 0.0;
    for (int k = 0; k < n; ++k) norm += v[k]*v[k];
    norm = std::sqrt(norm);
    for (int k = 0; k < n; ++k) v[k] /= norm;

    return v;
}


std::pair<std::vector<double>, std::vector<pp::vector>> eigen_rank2_update(std::vector<double> d_in,
                                        std::vector<double> u_in,
                                        int p)
{
    int n = (int)d_in.size();

    std::vector<int> idx(n);
    std::iota(idx.begin(), idx.end(), 0);
    std::sort(idx.begin(), idx.end(),
              [&](int a, int b){ return d_in[a] < d_in[b]; });

    std::vector<double> d(n), u(n);
    int p_sorted = -1;
    for (int i = 0; i < n; ++i) {
        d[i] = d_in[idx[i]];
        u[i] = u_in[idx[i]];
        if (idx[i] == p) p_sorted = i;
    }
    p = p_sorted;

    const double eps = 1e-10;
    double spread = std::max(d[n-1] - d[0], 1.0);

    std::vector<std::pair<double,double>> intervals;
    intervals.push_back({ d[0] - 2.0*spread, d[0] - eps });
    for (int k = 0; k < n-1; ++k)
        if (d[k+1] - d[k] > 2.0*eps)
            intervals.push_back({ d[k]+eps, d[k+1]-eps });
    intervals.push_back({ d[n-1]+eps, d[n-1] + 2.0*spread });

    std::vector<double> eigenvalues;

    for (auto& [lo, hi] : intervals) {
        double f0, df0, f1, df1;
        secular_one(d, u, p, lo, f0, df0);
        secular_one(d, u, p, hi, f1, df1);
        if (f0 * f1 >= 0.0) continue;

        // A few bisection steps to get a good starting guess
        // so newton() converges in O(1) iterations regardless of n
        double a = lo, b = hi;
        for (int bisect = 0; bisect < 6; ++bisect) {
            double mid = 0.5*(a + b);
            double fm, dfm;
            secular_one(d, u, p, mid, fm, dfm);
            if (f0 * fm < 0.0) { b = mid; f1 = fm; }
            else               { a = mid; f0 = fm; }
        }

        // Now hand off to newton() from this tight bracket
        double a_bracket = a, b_bracket = b;
        auto F = [&](pp::vector x) -> pp::vector {
            double xi = x[0];
            if (xi <= a_bracket) xi = a_bracket + eps;
            if (xi >= b_bracket) xi = b_bracket - eps;
            double f, df;
            secular_one(d, u, p, xi, f, df);
            pp::vector fx(1);
            fx[0] = f;
            return fx;
        };

        pp::vector x0(1);
        x0[0] = 0.5*(a + b);

        pp::vector root = newton(F, x0, 1e-12, 1e-14, 200, a_bracket, b_bracket);
        eigenvalues.push_back(root[0]);
    }

    for (int k = 0; k < n; ++k)
        if (k != p && std::abs(u[k]) < 1e-15)
            eigenvalues.push_back(d[k]);

    std::sort(eigenvalues.begin(), eigenvalues.end());
    
    // Compute eigenvectors for each eigenvalue
    std::vector<pp::vector> eigenvectors;
    for (double lambda : eigenvalues)
        eigenvectors.push_back(compute_eigenvector(d, u, p, lambda));

    return {eigenvalues, eigenvectors};
}


pp::matrix build_A(const std::vector<double>& d,
                   const std::vector<double>& u,
                   int p)
{
    int n = (int)d.size();
    pp::matrix A(n, n);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            A[i,j] = (i==j ? d[i] : 0.0)
                   + (i==p ? u[j] : 0.0)
                   + (j==p ? u[i] : 0.0);
    return A;
}

// Verify: compute residual ||A*v - lambda*v|| for each eigenpair
void verify_eigenvectors(const std::vector<double>& d,
                          const std::vector<double>& u,
                          int p,
                          const std::vector<double>& eigenvalues,
                          const std::vector<pp::vector>& eigenvectors)
{
    int n = (int)d.size();
    pp::matrix A = build_A(d, u, p);
    std::cout << "  Eigenvector residuals ||A*v - lambda*v||:\n";
    for (int i = 0; i < (int)eigenvalues.size(); ++i) {
        double lambda = eigenvalues[i];
        const pp::vector& v = eigenvectors[i];
        // Compute A*v - lambda*v
        double res = 0.0;
        for (int r = 0; r < n; ++r) {
            double Av_r = 0.0;
            for (int c = 0; c < n; ++c)
                Av_r += A[r,c] * v[c];
            double diff = Av_r - lambda * v[r];
            res += diff * diff;
        }
        std::cout << "  lambda[" << i << "] = " << std::setw(14)
                  << std::setprecision(8) << lambda
                  << "  residual = " << std::scientific << std::sqrt(res) << "\n";

        // std::cout << "  lambda[" << i << "] = " << std::setw(14)
        //         << std::setprecision(8) << lambda << "\n";
        std::cout << "  eigenvector: (";
        for (int k = 0; k < n; ++k)
            std::cout << std::setprecision(6) << v[k] << (k<n-1 ? ", " : "");
        std::cout << ")\n";
        // std::cout << "  residual = " << std::scientific << std::sqrt(res) << "\n\n";
    }
    std::cout << "\n";
    
}