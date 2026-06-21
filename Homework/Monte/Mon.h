//#ifndef MON_H
//#define MON_H

#include <vector>
#include <functional>
#include <utility>

namespace pp{
    std::pair<double, double> plainmc(
        std::function<double(const std::vector<double>&)> f,
        const std::vector<double>& a,
        const std::vector<double>& b,
        int N
    );


    // Quasi Monte Carlo (Halton-based)
    std::pair<double, double> quasi_mc(
        std::function<double(const std::vector<double>&)> f,
        const std::vector<double>& a,
        const std::vector<double>& b,
        int N
    );

    // Halton sequence (helper function)
    double halton(int index, int base);
}
//#endif