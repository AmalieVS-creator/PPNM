#include <iostream>
#include <cmath>
#include <random>
#include "matrix.h"

int main() {

    // ----- 1. Generate random tall matrix A -----
    int n = 6;
    int m = 3;

    pp::matrix A(n, m);

    std::mt19937 gen(42);
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            A(i,j) = dist(gen);

    A.print("Random matrix A:");

    // ----- 2. QR decomposition -----
    pp::QR decomp(A);

    pp::matrix& Q = decomp.Q;
    pp::matrix& R = decomp.R;

    Q.print("Q:");
    R.print("R:");

    // ----- 3. Check R is upper triangular -----
    bool upper = true;

    for (int i = 0; i < R.size1(); ++i)
        for (int j = 0; j < i; ++j)
            if (std::abs(R(i,j)) > 1e-10)
                upper = false;

    std::cout << "R upper triangular: "
              << (upper ? "TRUE\n" : "FALSE\n");

    // ----- 4. Check Q^T Q = I -----
    pp::matrix Qt = Q.transpose();
    pp::matrix QtQ = Qt * Q;
    QtQ.threshold();
    QtQ.print("Q^T Q = I ?");

    // ----- 5. Check QR = A -----
    pp::matrix QR = Q * R;
    pp::matrix diff = QR - A;
    diff.threshold();
    diff.print("Is QR = A, then QR - A = 0:");

     // ----- 6. Test solve() for square system -----
    int s = m; // use square system of size m×m for solve
    pp::matrix As(s, s);
    pp::vector b(s);

    for (int i = 0; i < s; ++i)
        for (int j = 0; j < s; ++j)
            As(i,j) = dist(gen);

    for (int i = 0; i < s; ++i)
        b[i] = dist(gen);
    
    std::cout<<" "<<"\n\n\n";
    
    std::cout<<"----------Solving linear equations------------"<<"\n";
    std::cout << "\nRandom square matrix As:\n";
    As.print();
    std::cout << "Random vector b:\n";
    b.print();

    pp::QR qrSolve(As);
    pp::vector x = qrSolve.solve(b);

    std::cout << "Solution vector x:\n";
    x.print();

    pp::vector Ax = As * x;
    std::cout << "Does A*x=b?:\n";
    Ax.print();
    std::cout<<" "<<"\n\n\n";

    // Compute error ||Ax - b||
    double err = 0;
    for (int i = 0; i < s; ++i)
        err += (Ax[i] - b[i]) * (Ax[i] - b[i]);
    err = std::sqrt(err);


    // Determinant 
    std::cout<<"----------Determinant-----------"<<"\n";
    std::cout<<"Determinant of R = "<<decomp.det()<<"\n\n\n";


    // Inverse
    std::cout<<"-----------Inverse-----------"<<"\n";
    As.print("Random square matrix A");
    pp::matrix Ainv=qrSolve.inverse();
    Ainv.print("Inverse A matrix");
    pp::matrix I=As*Ainv;
    I.threshold();
    I.print("Is A*A^-1=I?");



    return 0;
}