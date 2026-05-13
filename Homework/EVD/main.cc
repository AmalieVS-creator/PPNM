#include <iostream>
#include <cmath>
#include <random>
#include "matrix.h"
#include "evd.h"
#include "QR.h"

int main(){
    int n = 5; // size of matrix

    pp::matrix A(n, n);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1.0, 1.0);

    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double value = dist(gen);
            A[i][j] = value;
            A[j][i] = value; // enforce symmetry
        }
    }

    A.print("Random symmetric matrix A: ");
    pp::EVD EVD_A(A);
    pp::matrix& V = EVD_A.V;
    pp::vector& w=EVD_A.w;
    V.print("Matrix V: ");
    w.print("Vector w: ");

    pp::matrix D(n,n);
    for (int i=0; i<n; i++){
        D(i,i)=w[i];
    }
    D.print("Diagonal matrix D: ");

    pp::matrix Vt=V.transpose();
    pp::matrix VtAV=Vt*A*V;
    VtAV.threshold();
    VtAV.print("V^T AV = D ?");

    pp::matrix VDVt=V*D*Vt;
    VDVt.threshold();
    VDVt.print("VDV^T = A ?");

    pp::matrix VtV=Vt*V;
    VtV.threshold();
    VtV.print("V^T*V = I ?");

    pp::matrix VVt=V*Vt;
    VVt.threshold();
    VVt.print("V*V^T = I ?");


    return 0;
}