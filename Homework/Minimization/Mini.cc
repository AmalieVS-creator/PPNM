#include <functional>
#include <cmath>
#include <limits>
#include "QR.h"


pp::vector gradient(std::function<double(const pp::vector&)> phi, pp::vector x){
    double phix=phi(x);
    pp::vector phig(x.size());
    for (int i=0; i<x.size(); i++){
        double dxi=(1+std::fabs(x[i]))*std::pow(2, -26);
        x[i]+=dxi;
        phig[i]=(phi(x)-phix)/dxi;
        x[i]-=dxi;
    }
    return phig;
}

pp::matrix hessian(std::function<double(const pp::vector&)> phi, pp::vector x){
    pp::matrix H(x.size(), x.size());
    pp::vector phigx=gradient(phi, x);
    for (int j=0; j<x.size(); j++){
        double dxj=(1+std::fabs(x[j]))*std::pow(2, -13);
        x[j]+=dxj;
        pp::vector phidg=gradient(phi, x)-phigx;
        for (int i=0; i<x.size(); i++){
            H(i, j) = phidg[i] / dxj;
        }
        x[j]-=dxj;
    }
    return H;
}

std::pair<pp::vector, int> newton(std::function<double(pp::vector)> phi, pp::vector x, double acc){
    int n_steps = 0;
    while (true){
        n_steps += 1;
        pp::vector g=gradient(phi, x);
        if (g.norm() < acc){break;}
        pp::matrix H=hessian(phi, x);
        // for (int i=0; i<H.size1(); i++){H(i, i) += 1e-6;}
        // pp::QR QRH(H);
        // pp::vector dx=QRH.solve(-g);
        pp::QR decomp(H);
        pp::vector dx = decomp.solve(-g);
        double lambda=1;
        while (lambda >=1.0/1024.0){
            if (phi(x+lambda*dx)<phi(x)){break;}
            lambda/=2;
        }
        x+=lambda*dx;
    };
    return {x, n_steps};
}
    
    