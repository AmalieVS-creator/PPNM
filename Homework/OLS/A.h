#pragma once
#include "QR.h"
#include "matrix.h"
#include <vector>
#include <functional>
#include <tuple>

namespace pp {

inline std::tuple<vector, matrix> lsfit(
    const std::vector<std::function<double(double)>>& fs,
    const pp::vector& x,
    const pp::vector& y,
    const pp::vector& dy
){
    int n = x.size();
    int m = fs.size();

    pp::matrix A(n,m);
    pp::vector b(n);

    for (int i=0; i<n; i++){
        b[i] = y[i]/dy[i];
        for(int k=0;k<m;k++){
            A(i,k) = fs[k](x[i]) / dy[i];
        }
    }

    pp::QR qr(A);
    pp::vector c = qr.solve(b);
    pp::matrix R_inv=qr.inverse_R();
    pp::matrix sigma=R_inv*R_inv.transpose();

    return {c, sigma};
}

}