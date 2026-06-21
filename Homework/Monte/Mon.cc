#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <functional>
#include <utility>



namespace pp{
// Plain Monte Carlo integration
std::pair<double, double> plainmc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N
) {
    int dim = a.size();

    // Compute volume V
    double V = 1.0;
    for (int i = 0; i < dim; i++) {
        V *= (b[i] - a[i]);
    }

    // Random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(0.0, 1.0);

    double sum1 = 0.0;
    double sum2 = 0.0;

    for (int i = 0; i < N; i++) {
        std::vector<double> x(dim);

        for (int j = 0; j < dim; j++) {
            x[j] = a[j] + dist(gen) * (b[j] - a[j]);
        }

        double fx = f(x);
        sum1 += fx;
        sum2 += fx * fx;
    }

    double mean = sum1 / N;
    double sigma = std::sqrt(sum2 / N - mean * mean);

    return {mean * V, sigma * V / std::sqrt(N)};
}

// Halton sequence
double halton(int index, int base) {
    double result = 0.0, f = 1.0 / base;
    while (index > 0) {
        result += f * (index % base);
        index /= base;
        f /= base;
    }
    return result;
}

// QMC integrator with two sequences
std::pair<double,double> quasi_mc(
    std::function<double(const std::vector<double>&)> f,
    const std::vector<double>& a,
    const std::vector<double>& b,
    int N
) {
    int dim = a.size();

    std::vector<int> primes1 = {2,3,5,7,11,13,17,19};
    std::vector<int> primes2 = {23,29,31,37,41,43,47,53};

    double V = 1.0;
    for (int i = 0; i < dim; i++)
        V *= (b[i] - a[i]);

    double sum1 = 0.0, sum2 = 0.0;

    for (int i = 1; i <= N; i++) {
        std::vector<double> x1(dim), x2(dim);

        for (int d = 0; d < dim; d++) {
            double h1 = halton(i, primes1[d]);
            double h2 = halton(i, primes2[d]);

            x1[d] = a[d] + h1 * (b[d] - a[d]);
            x2[d] = a[d] + h2 * (b[d] - a[d]);
        }

        sum1 += f(x1);
        sum2 += f(x2);
    }

    double I1 = (sum1 / N) * V;
    double I2 = (sum2 / N) * V;

    double error = std::abs(I1 - I2);

    return {I1, error};
}
}