#include <iostream>
#include <cmath>
#include <vector>
#include <limits>
#include <fstream>
#include "rec.h"

int main()
{
    auto f = [](double x) {
        return std::sqrt(x);
    };
    auto f2 = [](double x) {
        return 1/std::sqrt(x);
    };
    auto f3 = [](double x) {
        return std::sqrt(1-std::pow(x,2));
    };
    auto f4 = [](double x) {
        return std::log(x)/std::sqrt(x);
    };

    double test1 = pp::integrate(f, 0.0, 1.0);
    double test2 = pp::integrate(f2, 0.0, 1.0);
    double test3 = pp::integrate(f3, 0.0, 1.0);
    double test4 = pp::integrate(f4, 0.0, 1.0);

    bool approx1 = pp::approx(test1, 2.0/3.0);
    bool approx2 = pp::approx(test2, 2.0);
    bool approx3 = pp::approx(test3, 3.14/4.0);
    bool approx4 = pp::approx(test4, -4.0);

    std::cout << "Test 1 = " << test1 << '\n';
    std::cout << "Test 2 = " << test2 << '\n';
    std::cout << "Test 3 = " << test3 << '\n';
    std::cout << "Test 4 = " << test4 << '\n';

    std::cout << "sqrt(x): q="<<test1<<".   Within accuracy: "<<approx1<<"\n";
    std::cout << "1/sqrt(x): q="<<test2<<".   Within accuracy: "<<approx2<<"\n";
    std::cout << "sqrt(1-x^2): q="<<test3<<".   Within accuracy: "<<approx3<<"\n";
    std::cout << "log(x)/sqrt(x): q="<<test4<<".   Within accuracy: "<<approx4<<"\n";

    std::ofstream curve("erf_curve.dat");

    for (double z = -3.0; z <= 3.0; z += 0.1)
    {
        curve << z << " " << pp::erf(z) << "\n";
    }


    const double erf = 0.84270079294971486934;

    std::ofstream file("erf_error_acc.dat");

    for (double acc = 0.1; acc >= 1e-9; acc /= 10.0)
    {
        double approx = pp::erf(1.0, acc, 0.0);
        double error  = std::abs(erf - approx);

        file << acc << " " << error << "\n";
    }




    // number B

    // number B

 std::cout << "\n Opgave B\n";   
// ---------------- 1/sqrt(x) ----------------
pp::ncalls = 0;

int ncalls_cc1 = 0;
auto f_cc1 = [&ncalls_cc1](double x)
{
    ncalls_cc1++;
    return 1.0 / std::sqrt(x);
};

double q_cc1 = pp::integrate_cc_rec(f_cc1, 0.0, 1.0, 1e-3, 1e-3);

std::cout << "1/sqrt(x): q = " << q_cc1
          << " | ncalls = " << ncalls_cc1 << "\n";


int ncalls_cc1_or = 0;
auto f_cc1_or = [&ncalls_cc1_or](double x)
{
    ncalls_cc1_or++;
    return 1.0 / std::sqrt(x);
};          

double q_cc1_or = pp::integrate(f_cc1_or, 0.0, 1.0);

std::cout << "Ordinary 1/sqrt(x): q = " << q_cc1_or
          << " | ncalls = " << ncalls_cc1_or << "\n";
// ---------------- log(x)/sqrt(x) ----------------
pp::ncalls = 0;

int ncalls_cc2 = 0;
auto f_cc2 = [&ncalls_cc2](double x)
{
    ncalls_cc2++;
    return std::log(x) / std::sqrt(x);
};

double q_cc2 = pp::integrate_cc_rec(f_cc2, 0.0, 1.0, 1e-3, 1e-3);

std::cout << "log(x)/sqrt(x): q = " << q_cc2
          << " | ncalls = " << ncalls_cc2 << "\n";


int ncalls_cc2_or = 0;
auto f_cc2_or = [&ncalls_cc2_or](double x)
{
    ncalls_cc2_or++;
    return std::log(x) / std::sqrt(x);
};

double q_cc2_or = pp::integrate(f_cc2_or, 0.0, 1.0);

std::cout << "Ordinary log(x)/sqrt(x): q = " << q_cc2_or
          << " | ncalls = " << ncalls_cc2_or << "\n";

// ---------------- infinite integral ----------------
//const double infa = std::numeric_limits<double>::infinity();
const double infb = std::numeric_limits<double>::infinity();

pp::ncalls = 0;

int ncalls_cc3 = 0;
auto f_cc3 = [&ncalls_cc3](double x)
{
    ncalls_cc3++;
    return std::exp(-x);
};

double q_cc3 = pp::integrate(f_cc3, 0, infb);

// bool ok = pp::approx(q_cc3, 1.0);

std::cout << "exp(-x) from 0 to inf: q = " << q_cc3
          << " | ncalls = " << ncalls_cc3 << "\n";
}

