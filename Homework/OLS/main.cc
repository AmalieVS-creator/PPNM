#include <iostream>
#include <cmath>
#include <random>
#include <functional>
#include <vector>
#include "matrix.h"
#include "QR.h"
#include "A.h"
#include <fstream>


int main(){

    std::vector<std::function<double(double)>> fs = {
        [](double x){ return 1.0; },
        [](double x){ return x; }
    };

    pp::vector x={1, 2, 3, 4, 6, 9, 10, 13, 15};
    pp::vector y={117, 100, 88, 72, 53, 29.5, 25.2, 15.2, 11.1};
    pp::vector dy={6, 5, 4, 4, 4, 3, 3, 2, 2};

    pp::vector lny(x.size());
    pp::vector dlny(x.size());

    for (int i=0; i<x.size(); i++){
        lny[i]=std::log(y[i]);
        dlny[i]=dy[i]/y[i];
    }

    auto [c, sigma]=lsfit(fs, x, lny, dlny);
    double a = exp(c[0]);
    double lambda = -c[1];
    std::cout<<"Fitting to data.\n\ta: "<<a<<"\n\tlambda: "<<lambda<<"\n"; 

    std::ofstream file("decay.dat");

    for(double tt=0; tt<=16; tt+=0.1){
        double fit = a*exp(-lambda*tt);
        file << tt << " " << fit << "\n";
    }
    
    std::ofstream data("data.dat");

    double halflife = std::log(2)/lambda; 
    std::cout<<"Halflife = "<<halflife<<" days\n";
    std::cout<<"Real Halflife = 3.631 days\n";
    

    for(int i=0;i<x.size();i++){
        data << x[i] << " " << y[i] << " " << dy[i] << "\n";
    }
    
    sigma.print("Uncertainty matrix: ");
    double a_error=std::sqrt(sigma[0][0]);
    double lambda_error=std::sqrt(sigma[1][1]);

    std::cout<<"Uncertainty on a= "<<a_error<<"\n";
    std::cout<<"Uncertainty on lambda= "<<lambda_error<<"\n";

    double halflife_error=std::log(2)/std::pow(lambda,2)*lambda_error;
    std::cout<<"Uncertainty on halflife= "<<halflife_error<<"\n";
}