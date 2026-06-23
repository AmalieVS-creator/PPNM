#include <functional>
#include "root.h"
#include "QR.h"

pp::matrix jacobian(std::function<pp::vector(pp::vector)> f, pp::vector x, pp::vector fx){
    int n = x.size();
    pp::matrix J(n,n);
    for (int i = 0; i<n; i++){
        for (int j = 0; j<n; j++){
            double dxj=std::fabs(x[j])*std::pow(2,-26);
            x[j]+=dxj;
            pp::vector df=f(x)-fx;
            J(i,j) = df[i]/dxj;
            x[j]-=dxj;
        }
    }
    return J;
}

pp::vector newton(std::function<pp::vector(pp::vector)> f, pp::vector x, double acc, double alpha_min, int max_iter){
    pp::vector fx=f(x);
    for (int i=0; i<max_iter; i++){
        // double norm = pp::norm(fx);
        if (fx.norm() < acc){break;}
        pp::matrix J=jacobian(f, x, fx);
        pp::QR QRJ(J);
        pp::vector Dx=QRJ.solve(-fx);
        double alpha=1;
        pp::vector fz, z;
        while (true){
            z=x+alpha*Dx;
            fz=f(z);
            if (fz.norm()<(1-alpha/2)*fx.norm()){break;}
            // if (fz.norm()<fx.norm()){break;}
            if (alpha<alpha_min){break;}
            alpha/=2;
        }
        x=z;
        fx=fz;
    }
    return x;
}

// double newton1d(
//     std::function<double(double)> f,
//     double x)
// {
//     for(int iter=0; iter<50; iter++)
//     {
//         double fx = f(x);

//         if(std::abs(fx) < 1e-10)
//             break;

//         double dx = (std::abs(x)+1.0)*1e-8;

//         double dfx =
//             (f(x+dx)-fx)/dx;

//         x -= fx/dfx;
//     }

//     return x;
// }