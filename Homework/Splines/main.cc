#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include "LS.h"

int main(){
        // x-values
    std::vector<double> x = {0,0.5,1,1.5,2,2.5,3,3.5,4,4.5,
                             5,5.5,6,6.5,7,7.5,8,8.5,9};

    // y-values
    std::vector<double> y(x.size());

    for(size_t i=0;i<x.size();i++)
        y[i]=std::cos(x[i]);

    // spline
    pp::qspline qs(x,y);

    // files
    std::ofstream data("data.dat");
    std::ofstream linear("linear.dat");
    std::ofstream quadratic("quadratic.dat");

    // original data
    for(size_t i=0;i<x.size();i++)
        data << x[i] << " " << y[i] << "\n";

    for(double z = 0; z <= 9; z += 0.01){

    // Linear spline
    double lin    = pp::linterp(x,y,z);
    double linInt = pp::linterpInteg(x,y,z);

    linear << z << " "
           << lin << " "
           << linInt << "\n";

    // Quadratic spline
    double s  = qs.eval(z);
    double ds = qs.deriv(z);
    double S  = qs.integ(z);

    // Exact values
    double exact  = std::cos(z);
    double dexact = -std::sin(z);
    double Iexact = std::sin(z);

    quadratic << z << " "
              << s << " "
              << exact << " "
              << ds << " "
              << dexact << " "
              << S << " "
              << Iexact << "\n";
}

    return 0;
}