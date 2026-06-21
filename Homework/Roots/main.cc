#include <iostream>
#include <cmath>
#include <functional>
#include <vector>
#include <fstream>

#include "matrix.h"
#include "QR.h"
#include "root.h"
#include "RKE.h"

// Made with AI

// ===================== SHOOTING FUNCTION =====================

auto make_shoot_energy()
{
    return [&](double E, double rmin, double rmax, double acc, double eps)
    {
        auto F = [&](double r, pp::vector y)
        {
            pp::vector dydr(2);

            double f  = y[0];
            double fp = y[1];

            dydr[0] = fp;
            dydr[1] = -2.0 * (E + 1.0 / r) * f;

            return dydr;
        };

        pp::vector y0(2);
        y0[0] = rmin - rmin * rmin;
        y0[1] = 1 - 2 * rmin;

        auto [rvals, yvals] =
            driver(F, rmin, rmax, y0, 0.1, acc, eps);

        return yvals.back()[0];
    };
}

int main()
{
    // =========================================================
    // PART A: YOUR EXISTING ROSENBROCK / HIMMELBLAU (UNCHANGED)
    // =========================================================

    std::function<pp::vector(pp::vector)> rosen = [](pp::vector v)
    {
        pp::vector grad(2);

        double x = v[0];
        double y = v[1];

        grad[0] = 2*(200*x*x*x - 200*x*y + x - 1);
        grad[1] = 200*(y - x*x);

        return grad;
    };

    pp::vector init(2);
    init[0] = -2;
    init[1] = 2;

    pp::vector rosen_rod = newton(rosen, init);

    std::cout << "Rosenbrock min: "
              << rosen_rod[0] << " " << rosen_rod[1] << "\n";

    std::function<pp::vector(pp::vector)> himmel = [](pp::vector v)
    {
        pp::vector grad(2);

        double x = v[0];
        double y = v[1];

        grad[0] = 2*(x*x + y - 11)*2*x + 2*(x + y*y - 7);
        grad[1] = 2*(x*x + y - 11) + 2*(x + y*y - 7)*2*y;

        return grad;
    };

    pp::vector init2(2);
    init2[0] = -2;
    init2[1] = 2;

    pp::vector himmel_rod = newton(himmel, init2);

    std::cout << "Himmelblau min: "
              << himmel_rod[0] << " " << himmel_rod[1] << "\n";

    // =========================================================
    // PART B: HYDROGEN SHOOTING METHOD
    // =========================================================

    double rmin = 1e-3;
    double rmax = 8.0;

    auto shoot_energy = make_shoot_energy();

    // ---- M(E) = boundary value at rmax ----
    std::function<pp::vector(pp::vector)> M =
    [&](pp::vector x)
    {
        pp::vector y(1);
        y[0] = shoot_energy(x[0], rmin, rmax, 0.01, 0.01);
        return y;
    };

    // ---- Newton in energy space ----
    pp::vector guess(1);
    guess[0] = -0.5;

    pp::vector root = newton(M, guess);

    double E0 = root[0];

    std::cout << "\nGround state energy E0 = " << E0 << "\n";

    // =========================================================
    // RECOMPUTE WAVEFUNCTION AT E0
    // =========================================================

    auto F = [&](double r, pp::vector y)
    {
        pp::vector dydr(2);

        dydr[0] = y[1];
        dydr[1] = -2.0 * (E0 + 1.0 / r) * y[0];

        return dydr;
    };

    pp::vector y0(2);
    y0[0] = rmin - rmin * rmin;
    y0[1] = 1 - 2 * rmin;

    auto [rvals, yvals] =
        driver(F, rmin, rmax, y0, 0.1, 0.01, 0.01);

    // =========================================================
    // OUTPUT FOR PLOTTING
    // =========================================================

    std::ofstream out("wave.dat");

    for (size_t i = 0; i < rvals.size(); i++)
    {
        double r = rvals[i];
        double numerical = yvals[i][0];
        double exact = r * std::exp(-r);

        out << r << " " << numerical << " " << exact << "\n";
    }

    std::cout << "Data written to wave.dat\n";


    std::cout << "\n================ CONVERGENCE STUDY ================\n";

    std::vector<double> rmax_list = {6.0, 8.0, 10.0, 12.0};
    std::vector<double> rmin_list = {1e-2, 1e-3, 1e-4};

    for (double rmax_test : rmax_list)
    {
        double rmin_test = 1e-3;

        auto shoot_energy = make_shoot_energy();

        std::function<pp::vector(pp::vector)> Mtest =
        [&](pp::vector x)
        {
            pp::vector y(1);
            y[0] = shoot_energy(x[0], rmin_test, rmax_test, 0.01, 0.01);
            return y;
        };

        pp::vector guess(1);
        guess[0] = -0.5;

        pp::vector root = newton(Mtest, guess);

        std::cout << "rmax = " << rmax_test
                << " -> E0 = " << root[0] << "\n";
    }

    std::cout << "\n--- rmin study ---\n";

    double rmax_fixed = 8.0;

    for (double rmin_test : rmin_list)
    {
        auto shoot_energy = make_shoot_energy();

        std::function<pp::vector(pp::vector)> Mtest =
        [&](pp::vector x)
        {
            pp::vector y(1);
            y[0] = shoot_energy(x[0], rmin_test, rmax_fixed, 0.01, 0.01);
            return y;
        };

        pp::vector guess(1);
        guess[0] = -0.5;

        pp::vector root = newton(Mtest, guess);

        std::cout << "rmin = " << rmin_test
                << " -> E0 = " << root[0] << "\n";
    }

    std::cout << "\n================ END STUDY ================\n";

    std::cout << "\n--- acc / eps study ---\n";

    double rmin_fixed = 1e-3;


    // progressively tighter tolerances
    std::vector<std::pair<double,double>> tol_list = {
        {1e-1, 1e-1},
        {1e-2, 1e-2},
        {1e-3, 1e-3},
        {1e-4, 1e-4}
    };

    for (auto [acc, eps] : tol_list)
    {
        auto shoot_energy = make_shoot_energy();

        std::function<pp::vector(pp::vector)> Mtest =
        [&](pp::vector x)
        {
            pp::vector y(1);
            y[0] = shoot_energy(x[0], rmin_fixed, rmax_fixed, acc, eps);
            return y;
        };

        pp::vector guess(1);
        guess[0] = -0.5;

        pp::vector root = newton(Mtest, guess);

        std::cout << "acc = " << acc
                << ", eps = " << eps
                << " -> E0 = " << root[0] << "\n\n";
    
        std::cout << "acc=" << acc
            << " eps=" << eps
            << " E0=" << root[0]
            << " M(E0)=" << shoot_energy(root[0], rmin_fixed, rmax_fixed, acc, eps)
            << "\n";
    }
    return 0;
}