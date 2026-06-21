#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <vector>
#include "matrix.h"
#include "QR.h"
#include "Mini.h"
#include <fstream>

// Made with AI

double breit_wigner(double E,
                     double M,
                     double Gamma,
                     double A = 1.0)
{
    double halfGamma = Gamma / 2.0;

    return A / ((E - M)*(E - M) + halfGamma*halfGamma);
}

int main(){
    auto rosen = [](const pp::vector& v) {
        double x = v[0];
        double y = v[1];
        return (1 - x)*(1 - x) + 100*(y - x*x)*(y - x*x);
    };

    pp::vector init(2);
    init[0] = -2;
    init[1] = 2;

    auto [sol, steps] = newton(rosen, init);
    std::cout<< "Minimum of Rosenbrock function (x,y)= "<<sol[0] <<" "<< sol[1]<< "\n";
    std::cout << "Steps = " << steps << "\n";


    auto himmel = [](const pp::vector& v) {
        double x = v[0];
        double y = v[1];
        return (x*x + y - 11)*(x*x + y - 11) + (x + y*y - 7)*(x + y*y - 7);
    };

    pp::vector init2(2);
    init2[0] = -2;
    init2[1] = 2;

    auto [sol2, steps2] = newton(himmel, init2);
    std::cout<< "Minimum of Himmelblau function (x,y)= "<<sol2[0] <<" "<< sol2[1]<< "\n";
    std::cout << "Steps = " << steps2 << "\n";


// Number B

// std::ifstream infile("data.dat");
// std::vector<double> energy, signal, error;
// double E, S, err;

// while (infile >> E >> S >> err) {
//     energy.push_back(E);
//     signal.push_back(S);
//     error.push_back(err);
// }

std::vector<double> energy, signal, error;

double E, S, err;
while (std::cin >> E >> S >> err) {
    energy.push_back(E);
    signal.push_back(S);
    error.push_back(err);
}

// NOW write data file
std::ofstream dataout("data.dat");
for (size_t i = 0; i < energy.size(); i++) {
    dataout << energy[i] << " "
            << signal[i] << " "
            << error[i] << "\n";
}

std::function<double(const pp::vector&)> D = [&](const pp::vector& v){
    double m=v[0];
    // double gamma=v[1];
    double gamma = std::exp(v[1]);
    double A = std::exp(v[2]);
    // double A=v[2];
    double D=0.0;

    for (size_t i = 0; i < energy.size(); ++i) {
    double diff = (breit_wigner(energy[i], m, gamma, A)
                    - signal[i]) / error[i];
    D += diff * diff;
    }

    return D;

    };

    // pp::vector p0(3);

    // // Initial guesses
    // p0[0] = 125.0;
    // p0[1] = 2.0;
    // p0[2] = 10.0;

    pp::vector p0(3);
    p0[0] = 125.0;           // M
    p0[1] = std::log(2.0);   // Gamma
    p0[2] = std::log(5.0); 

    auto [fit, steps_b] = newton(D, p0, 1e-6);

    double m = fit[0];
    double gamma = fit[1];
    double A = fit[2];

    std::cout << "Optimal parameters:\n";
    std::cout << "m = " << m
            << ", gamma = " << gamma
            << ", A = " << A << "\n";
    std::cout << "Number of steps = " << steps_b << "\n";

    std::ofstream out("fit.dat");

    // for (double e = energy.front(); e <= energy.back(); e += 0.2) {
    //     out << e << " " << breit_wigner(e, m, gamma, A) << "\n";
    // }
    if (energy.empty()) {
        std::cerr << "ERROR: No data loaded\n";
        return 1;
    }

    double emin = energy[0];
    double emax = energy[energy.size() - 1];

    for (double e = emin; e <= emax; e += 0.2) {
        out << e << " " << breit_wigner(e, m, gamma, A) << "\n";
    }



}