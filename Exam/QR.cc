#include<iostream>
#include<cstdio>
#include<iomanip>
#include<cmath>
#include<string>
#include<vector>
#include<initializer_list>
#include<functional>
#include<ranges>
#include "QR.h"

namespace pp {

QR::QR(const pp::matrix& A)
    : Q(A), R(A.size2(), A.size2())
{
    int n = A.size1();
    int m = A.size2();

    for (int i = 0; i < m; i++) {
        double norm = Q[i].norm();
        R(i, i) = norm;

        Q[i] /= norm;

        for (int j = i + 1; j < m; j++) {
            R(i, j) = pp::dot(Q[i], Q[j]);
            Q[j] -= Q[i] * R(i, j);
        }
    }
}


pp::vector QR::backsub(const vector& y) const {
    
    int m = R.size1();
    pp::vector x(m);
    for (int i = m - 1; i >= 0; i--) {
        double sum = y[i];
        for (int j = i + 1; j < m; j++) {
            sum -= R(i, j) * x[j];
        }
        x[i] = sum / R(i, i);
    }

    return x;
}

pp::vector QR::solve(const pp::vector& b) const {

    vector y=Q.transpose()*b;
    return backsub(y);
}

double QR::det() {
    int m = R.size1();
    double prod = 1;
    for (int i = 0; i < m; i++) {
        prod *= R(i, i);
    }
    return prod;
}

matrix QR::inverse() const {
    int m = R.size1();
    matrix B(m, m);

    for (int i = 0; i < m; i++) {
        pp::vector e(m);
        e[i] = 1.0;

        pp::vector x = solve(e);
        B[i] = x;
    }

    return B;
}

matrix QR::inverse_R() const {
    int m = R.size1();
    matrix B(m, m);

    for (int i = 0; i < m; i++) {
        pp::vector e(m);
        e[i] = 1.0;

        pp::vector x = backsub(e);
        B[i] = x;
    }

    return B;
}

pp::vector qr_eigenvalues(const pp::matrix& A)
{
    int n = A.size1();
    pp::matrix Ak = A;

    for (int iter = 0; iter < 20; iter++) {

        QR qr(Ak);
        pp::matrix Q = qr.Q;
        pp::matrix R = qr.R;

        Ak = R * Q;   // QR iteration step
    }

    pp::vector eig(n);
    for (int i = 0; i < n; i++) {
        eig[i] = Ak(i,i);
    }

    return eig;
}

}