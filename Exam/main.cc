#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <random>
#include "root.h"
#include "evd.h"
#include "symcol.h"


// Made with chat bot

int main(){
    std::cout <<"Three tests have been made at n={4, 3, 5}\n";
    std::cout <<"They show Secular and EVD estimate approximatly the same values. \n";
    std::cout <<"The eigenvector for each eigenvalue has also been computed,\n";
    std::cout <<"with residuales being very low.\n\n";

    auto run_test = [&](const std::string& label,
                        std::vector<double> d,
                        std::vector<double> u,
                        int p)
    {
        int n = (int)d.size();
        std::cout << "=== " << label << " ===\n";
        auto [eigs, vecs] = eigen_rank2_update(d, u, p);

        pp::matrix A = build_A(d, u, p);
        pp::EVD evd(A);
        std::vector<double> evd_eigs(n);
        for (int i = 0; i < n; ++i) evd_eigs[i] = evd.w[i];
        std::sort(evd_eigs.begin(), evd_eigs.end());

        std::cout << std::setw(5)  << "k"
                  << std::setw(20) << "Secular"
                  << std::setw(20) << "EVD"
                  << std::setw(20) << "|difference|" << "\n";
        std::cout << std::string(65, '-') << "\n";
        for (int i = 0; i < n; ++i) {
            double diff = std::abs(eigs[i] - evd_eigs[i]);
            std::cout << std::setw(5)  << i
                      << std::setw(20) << std::setprecision(10) << eigs[i]
                      << std::setw(20) << std::setprecision(10) << evd_eigs[i]
                      << std::setw(20) << std::scientific        << diff << "\n";
        }
        std::cout << "\n";
        verify_eigenvectors(d, u, p, eigs, vecs);
    };

    run_test("Test 1: D=diag(1,2,3,4), u=(1,1,1,1), p=1",
             {1,2,3,4}, {1,1,1,1}, 1);
    run_test("Test 2: D=diag(0,5,10), u=(2,-1,3), p=0",
             {0,5,10}, {2,-1,3}, 0);
    run_test("Test 3: D=diag(-2,-1,0,1,2), u=(1,0,-1,0,1), p=2",
             {-2,-1,0,1,2}, {1,0,-1,0,1}, 2);
    


    std::cout << "Now for big n\n";
    std::cout << "The scaling of the execution time has been computed for matrix up to size n=800\n";
    std::cout << "It is visualized in timing.svg. \n";
    std::cout << "It shows that secular function is slower for approx n<650,\n";
    std::cout << "but is much faster from approx n>650.\n";
    std::cout << "By plotting a quadratic formula it is clear,\n";
    std::cout << "the secular method scales quadraticly. \n";
    std::cout << "While the EVD scales cubically. ";

    std::ofstream out("timing.dat");
    out << "0 0 0\n";
    for (int n = 80; n<=800; n+=80){
        std::vector<double> d(n);
        std::vector<double> u(n);
        double p;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dist(0.0, 1.0);

        for (int i=0; i<n; i++){
            d[i] = dist(gen);
            u[i] = dist(gen);
        }
        p = dist(gen);


        auto start = std::chrono::high_resolution_clock::now();
        auto eigs = eigen_rank2_update(d, u, p);
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = stop - start;

        pp::matrix A = build_A(d, u, p);
        auto start_EVD = std::chrono::high_resolution_clock::now();
        pp::EVD evd(A);
        auto stop_EVD = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed_EVD = stop_EVD - start_EVD;
        
        out << n << " " << elapsed << " " << elapsed_EVD << "\n";
    }

 

    return 0;
}