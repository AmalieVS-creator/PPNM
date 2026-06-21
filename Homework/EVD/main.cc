#include <iostream>
#include <cmath>
#include <random>
#include <fstream>
#include "matrix.h"
#include "evd.h"
#include "QR.h"



int main(int argc,char** argv){

    // Number A 
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



    //  Number B

    double rmax = 10.0;
    double dr = 0.3;

    for(int i=1;i<argc;i++){
        std::string arg(argv[i]);

        if(arg=="-rmax" && i+1<argc)
            rmax = std::stod(argv[++i]);

        if(arg=="-dr" && i+1<argc)
            dr = std::stod(argv[++i]);
    }

    int npoints = (int)(rmax/dr)-1;
    pp::vector r(npoints);
    for(int i=0;i<npoints;i++)r[i]=dr*(i+1);

    pp::matrix H(npoints,npoints);
    for(int i=0;i<npoints-1;i++){
        H[i,i]  =-2*(-0.5/dr/dr);
        H[i,i+1]= 1*(-0.5/dr/dr);
        H[i+1,i]= 1*(-0.5/dr/dr);
    }
    H[npoints-1,npoints-1]=-2*(-0.5/dr/dr);

    for(int i=0;i<npoints;i++)H[i,i]+=-1/r[i];

    pp::EVD evd(H);
    int imin = 0;

    for(int i=1;i<npoints;i++){
        if(evd.w[i] < evd.w[imin])
            imin = i;
    }
    double E0 = evd.w[imin];

    std::cout << "Ground-state energy = " << E0 << "\n";

    pp::vector psi = evd.V[imin];

    double norm = 0.0;

    for(int i=0;i<npoints;i++)
        norm += psi[i]*psi[i]*dr;

    norm = std::sqrt(norm);

    psi /= norm;

    std::ofstream file("groundstate.dat");

    for (int i = 0; i < npoints; i++) {
        file << r[i] << " " << psi[i] << "\n";
    }
    // for (int i = 0; i < npoints; i++) {
    // double exact = r[i] * std::exp(-r[i]);

    // file << r[i]
    //     << " "
    //     << psi[i]
    //     << " "
    //     << exact
    //     << "\n";
    // }

    file.close();





    std::ofstream conv("dr_convergence.dat");

    double rmax_b = 10.0;

    // test several dr values
    std::vector<double> dr_values = {0.8, 0.5, 0.3, 0.2, 0.1, 0.05};

    for (double dr : dr_values) {

        int npoints = (int)(rmax_b / dr) - 1;

        pp::vector r(npoints);
        for (int i = 0; i < npoints; i++)
            r[i] = dr * (i + 1);

        pp::matrix H(npoints, npoints);

        // kinetic + potential (hydrogen s-wave)
        double t = -0.5 / (dr * dr);

        for (int i = 0; i < npoints; i++) {
            H(i, i) = -2.0 * t;
        }

        for (int i = 0; i < npoints - 1; i++) {
            H(i, i + 1) = t;
            H(i + 1, i) = t;
        }

        for (int i = 0; i < npoints; i++) {
            H(i, i) += -1.0 / r[i];
        }

        // diagonalize
        pp::EVD evd(H);

        // find lowest eigenvalue
        double E0 = evd.w[0];
        for (int i = 1; i < npoints; i++)
            if (evd.w[i] < E0) E0 = evd.w[i];

        std::cout << "dr = " << dr << " -> E0 = " << E0 << "\n";

        conv << dr << " " << E0 << "\n";
    }





    std::ofstream conv2("rmax_convergence.dat");

    // FIXED grid spacing
    double dr2 = 0.2;

    // vary rmax instead
    std::vector<double> rmax_values = {4.0, 6.0, 8.0, 10.0, 12.0, 14.0};

    for (double rmax2 : rmax_values) {

        int npoints = (int)(rmax2 / dr2) - 1;

        pp::vector r(npoints);
        for (int i = 0; i < npoints; i++)
            r[i] = dr * (i + 1);

        pp::matrix H(npoints, npoints);

        double t = -0.5 / (dr2 * dr2);

        // kinetic term
        for (int i = 0; i < npoints; i++) {
            H(i, i) = -2.0 * t;
        }

        for (int i = 0; i < npoints - 1; i++) {
            H(i, i + 1) = t;
            H(i + 1, i) = t;
        }

        // potential term
        for (int i = 0; i < npoints; i++) {
            H(i, i) += -1.0 / r[i];
        }

        // diagonalize
        pp::EVD evd(H);

        // extract lowest eigenvalue
        double E0 = evd.w[0];
        for (int i = 1; i < npoints; i++)
            if (evd.w[i] < E0)
                E0 = evd.w[i];

        std::cout << "rmax = " << rmax2 << " -> E0 = " << E0 << "\n";

        conv2 << rmax2 << " " << E0 << "\n";
    }




    std::ofstream wf("wavefunctions.dat");

    int nstates = 3;   // lowest 3 eigenstates

    for (int k = 0; k < nstates; k++) {

        // extract eigenvector k
        pp::vector vk = evd.V[k];

        // normalization constant
        double Const = 1.0 / std::sqrt(dr);

        for (int i = 0; i < npoints; i++) {

            double r_i = r[i];
            double fk  = Const * vk[i];

            wf << k << " " << r_i << " " << fk << "\n";
        }

        wf << "\n\n"; // blank line separates curves
    }

    return 0;
}