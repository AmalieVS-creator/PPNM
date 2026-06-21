#include <iostream>
#include <vector>
#include <cmath>
#include "Mon.h"
#include <fstream>


int main() {
    // Define f(x, y) = x^2 + y^2
    auto f = [](const std::vector<double>& x) {
        double x_val = x[0]; // x
        double y_val = x[1]; // y
        double r2 = x_val * x_val + y_val * y_val;
        if (r2<=1){return 1;} else return 0;
    };

    // Integration limits: x in [0,1], y in [0,1]
    std::vector<double> a = {-1.0, -1.0};
    std::vector<double> b = {1.0, 1.0};

    int N1 = 1000000;

    auto result = pp::plainmc(f, a, b, N1);

    std::cout<<"Area of unit circle:" <<"\n";
    std::cout << "Integral = " << result.first << std::endl;
    std::cout << "Estimated Error    = " << result.second << std::endl;
    std::cout << "Actual Error    = " << result.first-M_PI << std::endl;

    std::ofstream file("Error.dat");

    for(double N1=10; N1<=1e6; N1*=10){
        auto [results, errors] = pp::plainmc(f, a, b, N1);
        file << N1 << " " << errors << " " << abs(results-M_PI) << " " << 1/std::sqrt(N1) << "\n";
    }


    // new Integral
    auto f2 = [](const std::vector<double>& x) {
    double x_val = x[0]; // x
    double y_val = x[1]; // y
    double z_val = x[2];
    double tja = 1/(M_PI*M_PI*M_PI*(1-std::cos(x_val)*std::cos(y_val)*std::cos(z_val)));
    return tja;
    //if (tja<=1){return 1;} else return 0;
    };

    // Integration limits: x, y, z in [0,pi]
    std::vector<double> a2 = {0.0, 0.0, 0.0};
    std::vector<double> b2 = {M_PI, M_PI, M_PI};

    int N2 = 1000000;

    auto result2 = pp::plainmc(f2, a2, b2, N2);

    std::cout<<"Crazy integral:" <<"\n";
    std::cout << "Integral = " << result2.first << std::endl;
    std::cout << "Estimated Error    = " << result2.second << std::endl;
    std::cout << "Actual value = " << 1.3932039296856768591842462603255 << std::endl;
    std::cout << "Actual Error    = " << result2.first-1.3932039296856768591842462603255 << std::endl;


    //Opgave B

    auto fB = [](const std::vector<double>& x) {
        double x_val = x[0]; // x
        double y_val = x[1]; // y
        double r2 = x_val * x_val + y_val * y_val;
        if (r2<=1){return 1;} else return 0;
    };

    std::vector<double> a3 = {-1.0, -1.0};
    std::vector<double> b3 = {1.0, 1.0};

    int N3 = 100000;

    auto result3 = pp::quasi_mc(fB, a3, b3, N3);

    std::cout << "Opgave B: " << "\n";
    std::cout << "Integral = " << result3.first << "\n";
    std::cout << "Error    = " << result3.second << "\n";

    std::ofstream fileB("ErrorB.dat");

    for(double N3=10; N3<=1e6; N3*=10){
        auto [resultsB, errorsB] = pp::quasi_mc(fB, a3, b3, N3);
        fileB << N3 << " " << errorsB << " " << abs(resultsB-M_PI) << " " << 1/std::sqrt(N3) << "\n";
    }


    return 0;
}
