// #include <iostream>
// #include <vector>
// #include <cmath>
// #include <algorithm>
// #include <iomanip>

// #include "matrix.h"
// #include "symcol.h"
// #include "QR.h"
// #include "root.h"



// int main()
// {
//     int n = 5;

//     pp::vector d(n), u(n);

//     d[0]=1; d[1]=2; d[2]=4; d[3]=7; d[4]=10;
//     u[0]=0.2; u[1]=-0.3; u[2]=0.5; u[3]=0.1; u[4]=-0.4;

//     int p = 2;

//     /* fast method */
//     pp::vector fast = fast_eigenvalues(d,u,p);

//     /* QR method */
//     pp::matrix A = build_matrix(d,u,p);

//     pp::vector qr = qr_eigenvalues(A);

//     /* convert to STL vectors */
//     std::vector<double> a(fast.begin(), fast.end());
//     std::vector<double> b(qr.begin(), qr.end());

//     compare(a,b);
// }

#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include"root.h"

// assume pp::vector is std::vector<double>
// and pp::matrix, QR, norm etc already exist

double secular(double lambda,
               const pp::vector& d,
               const pp::vector& u,
               int p)
{
    double f = -(d[p] - lambda);

    for(int k = 0; k < (int)d.size(); k++)
    {
        if(k == p) continue;
        f += (u[k] * u[k]) / (d[k] - lambda);
    }
    return f;
}

// Wrap scalar -> vector for Newton
std::function<pp::vector(pp::vector)>
make_f(const pp::vector& d, const pp::vector& u, int p)
{
    return [&](pp::vector x)
    {
        pp::vector y(1);
        y[0] = secular(x[0], d, u, p);
        return y;
    };
}

// Evaluate derivative safely (optional debugging helper)
// double secular_fd(const pp::vector& d, const pp::vector& u, int p, double lambda)
// {
//     double f = 1.0; // derivative of -(d[p]-λ) is +1

//     for(int k = 0; k < (int)d.size(); k++)
//     {
//         if(k == p) continue;
//         double denom = (d[k] - lambda);
//         f += (u[k]*u[k]) / (denom * denom);
//     }
//     return f;
// }

int main()
{
    int n = 5;

    pp::vector d(n), u(n);

    d[0]=1; d[1]=2; d[2]=4; d[3]=7; d[4]=10;
    u[0]=0.2; u[1]=-0.3; u[2]=0.5; u[3]=0.1; u[4]=-0.4;

    std::vector<double> roots;

    // ---- Step 2: interval-based guesses ----
    std::vector<double> guess;

    // left of first eigenvalue
    guess.push_back(d[0] - 0.5);

    // between diagonals
    for(int i = 0; i < n-1; i++)
    {
        guess.push_back(0.5 * (d[i] + d[i+1]));
    }

    // right of last eigenvalue
    guess.push_back(d[n+1] + 0.5);

    // ---- Newton solve for each interval ----
    for(int i = 0; i < (int)guess.size(); i++)
    {
        pp::vector x(1);
        x[0] = guess[i];

        auto f = make_f(d, u, 0); // p doesn't matter here in this scalar version

        auto res = newton(
            f,
            x,
            1e-12,   // accuracy
            1e-10,   // alpha_min
            50
        );
        double root = res[0];

        // store (avoid duplicates)
        bool ok = true;
        for(double r : roots)
            if(std::fabs(r - root) < 1e-8) ok = false;

        if(ok) roots.push_back(root);
    }

    // ---- output ----
    std::cout << "Eigenvalues:\n";
    for(double r : roots)
        std::cout << r << "\n";

    return 0;
}