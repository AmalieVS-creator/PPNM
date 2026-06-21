#pragma once
#include <functional>
#include <limits>

namespace pp {

extern int ncalls;

double integrate(
    const std::function<double(double)> &func,
    double a,
    double b,
    double acc = 0.001,
    double eps = 0.001,
    double f2 = std::numeric_limits<double>::quiet_NaN(),
    double f3 = std::numeric_limits<double>::quiet_NaN()
);
double erf(double z, double acc=0.001, double eps=0.001);
bool approx(double a, double b, double eps=0.001);

double integrate_cc_rec(
    const std::function<double(double)> &f,
    double a,
    double b,
    double acc=0.001,
    double eps=0.001
);

// double integrate_cc(
//     const std::function<double(double)> &f,
//     double a,
//     double b,
//     double acc,
//     double eps
// ) {
//     return integrate_cc_rec(
//         f, a, b, acc, eps,
//         std::numeric_limits<double>::quiet_NaN(),
//         std::numeric_limits<double>::quiet_NaN()
//     );
// }

} // namespace pp