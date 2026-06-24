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


pp::vector newton(std::function<pp::vector(pp::vector)> f, pp::vector x, double acc, double alpha_min, int max_iter, double a, double b){
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
            // z=x+alpha*Dx;
            z = x + alpha*Dx;

            // enforce interval constraint
            if (z[0] <= a) z[0] = a + 1e-12;
            if (z[0] >= b) z[0] = b - 1e-12;
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

