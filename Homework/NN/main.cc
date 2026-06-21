#include <iostream>
#include "nn.h"
#include "matrix.h"
#include <cmath>
#include <fstream>

// Made with AI

int main()
{
    int N = 50;

    pp::vector x(N), y(N);

    // sample target function: g(x) = cos(5x - 1) * exp(-x^2)
    for (int i = 0; i < N; i++)
    {
        double xi = -1.0 + 2.0 * i / (N - 1);
        x[i] = xi;
        y[i] = std::cos(5*xi - 1) * std::exp(-xi*xi);
    }

    ann net(20);   // 20 hidden neurons

    net.train(x, y);

    // test output
    // for (int i = 0; i < 10; i++)
    // {
    //     double xi = -1.0 + 2.0 * i / 9.0;
    //     std::cout << xi << "  " << net.response(xi) << "\n";
    // }
    std::cout << "Test for plot in part A: "<< "\n";
    for (double x = -1.0; x <= 1.0; x += 0.2)
    {
        double exact = std::cos(5*x-1) * std::exp(-x*x);
        double approx = net.response(x);

        std::cout << x
                << " exact = " << exact
                << " approx = " << approx
                << " diff = " << approx - exact
                << "\n";
    }

    std::ofstream file("ann.dat");

    // smooth curve for NN output
    for (double x = -1.0; x <= 1.0; x += 0.01)
    {
        file << x << " " << net.response(x) << "\n";
    }
    file << "\n\n";

    // true function
    for (double x = -1.0; x <= 1.0; x += 0.01)
    {
        double y = std::cos(5*x - 1) * std::exp(-x*x);
        file << x << " " << y << "\n";
    }
    file << "\n\n";

    // training samples
    for (int i = 0; i < N; i++)
    {
        file << x[i] << " " << y[i] << "\n";
    }





    // ---------- Part (b) ----------

    // Create a NEW network for part (b)
    ann netB(20);
    netB.train(x, y);

    // Output the network response and its derivatives
    std::ofstream fout("partB.dat");

    for (double xx = -1.0; xx <= 1.0; xx += 0.01)
    {
        fout
            << xx << " "
            << netB.response(xx) << " "
            << netB.derivative(xx) << " "
            << netB.second_derivative(xx) << " "
            << netB.antiderivative(xx)
            << "\n";
    }

    fout.close();


    return 0;
}