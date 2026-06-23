#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "matrix.h"
#include "QR.h"
#include "root.h"

using namespace pp;

/* -------------------------------------------------------
   secular equation
------------------------------------------------------- */
double secular(double lambda,
               const pp::vector& d,
               const pp::vector& u,
               int p)
{
    double f = -(d[p] - lambda);   // THIS is the key term

    for(int k=0;k<d.size();k++)
    {
        if(k == p) continue;

        f += (u[k] * u[k]) / (d[k] - lambda);
    }

    return f;
}

/* -------------------------------------------------------
   1D Newton using YOUR root.cc function
------------------------------------------------------- */
double solve_root(const vector& d,
                  const vector& u,
                  int p,
                  double left,
                  double right)
{
    auto F = [&](double x)
    {
        return secular(x,d,u,p);
    };

    double x = 0.5*(left+right);

    for(int iter=0; iter<50; iter++)
    {
        double fx = F(x);

        if(std::abs(fx) < 1e-12)
            break;

        double dx = (std::abs(x)+1e-8)*1e-6;
        double dfx = (F(x+dx)-fx)/dx;

        double nx = x - fx/dfx;

        // KEEP INSIDE INTERVAL (IMPORTANT)
        if(nx <= left || nx >= right)
            nx = 0.5*(left+right);

        x = nx;
    }

    return x;
}

/* -------------------------------------------------------
   fast eigenvalues (O(n^2))
------------------------------------------------------- */
pp::vector fast_eigenvalues(const pp::vector& d,
                             const pp::vector& u,
                             int p)
{
    int n = d.size();

    std::vector<double> poles;
    for(int i=0;i<n;i++)
        if(i!=p) poles.push_back(d[i]);

    std::sort(poles.begin(), poles.end());

    pp::vector eigs(n);

    double M = 1.0;
    for(int i=0;i<n;i++)
        M += std::abs(d[i]) + std::abs(u[i]);

    int idx = 0;

    auto solve = [&](double left, double right)
    {
        auto F = [&](double x)
        {
            return secular(x,d,u,p);
        };

        double x = 0.5*(left+right);

        for(int i=0;i<50;i++)
        {
            double fx = F(x);

            if(std::abs(fx) < 1e-12)
                break;

            double dx = 1e-6;
            double dfx = (F(x+dx)-F(x-dx))/(2*dx);

            double nx = x - fx/dfx;

            if(nx <= left || nx >= right)
                nx = 0.5*(left+right);

            x = nx;
        }

        return x;
    };

    int idx2 = 0;

    eigs[idx2++] = solve(-M, poles.front());

    for(int i=0;i<(int)poles.size()-1;i++)
        eigs[idx2++] = solve(poles[i], poles[i+1]);

    eigs[idx2++] = solve(poles.back(), M);

    return eigs;
}

/* -------------------------------------------------------
   build full matrix A
------------------------------------------------------- */
matrix build_matrix(const vector& d,
                    const vector& u,
                    int p)
{
    int n = d.size();
    matrix A(n,n);

    for(int i=0;i<n;i++)
        A(i,i) = d[i];

    for(int i=0;i<n;i++)
    {
        A(p,i) += u[i];
        A(i,p) += u[i];
    }

    return A;
}

/* -------------------------------------------------------
   compare results
------------------------------------------------------- */
void compare(std::vector<double> a,
             std::vector<double> b)
{
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::cout << "\nComparison:\n";

    double max_err = 0;

    for(int i=0;i<a.size();i++)
    {
        double err = std::abs(a[i]-b[i]);
        max_err = std::max(max_err, err);

        std::cout << "i=" << i
                  << " fast=" << a[i]
                  << " QR=" << b[i]
                  << " err=" << err << "\n";
    }

    std::cout << "\nMax error = " << max_err << "\n";
}

