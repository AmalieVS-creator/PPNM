#include "rec.h"
#include <cmath>
#include <iostream>
#include <functional>

namespace pp {

int ncalls = 0;

double integrate(
    const std::function<double(double)> &func,
    double a,
    double b,
    double acc,
    double eps,
    double f2,
    double f3
) {
    double h = b - a;

    if (std::isinf(a) && std::isinf(b)) {
    auto g = [&](double t) {
        double x = t/(1-t*t);
        double dxdt = (1+t*t)/((1-t*t)*(1-t*t));
        return func(x)*dxdt;
    };
    return integrate_cc_rec(g, -1.0, 1.0, acc, eps);
    }

    if (!std::isinf(a) && std::isinf(b)) {
    auto g = [&](double t) {
        double x = a + t/(1-t);
        double dxdt = 1/((1-t)*(1-t));
        return func(x)*dxdt;
    };
    return integrate_cc_rec(g, 0.0, 1.0, acc, eps);
    }

    if (std::isinf(a) && !std::isinf(b)) {
    auto g = [&](double t) {
        double x = b + t/(1-t);
        double dxdt = 1/((1-t)*(1-t));
        return func(x)*dxdt;
    };
    return integrate_cc_rec(g, -1.0, 0.0, acc, eps);
    }

    if (std::isnan(f2)) {
        f2 = func(a + 2 * h / 6.0);
        f3 = func(a + 4 * h / 6.0);
    }

    double f1 = func(a + h / 6.0);
    double f4 = func(a + 5 * h / 6.0);

    double Q = (2*f1 + f2 + f3 + 2*f4) / 6.0 * (b - a);
    double q = (f1 + f2 + f3 + f4) / 4.0 * (b - a);

    double err = std::fabs(Q - q);
    double tol = acc + eps * std::fabs(Q);

    if (err < tol) {
        return Q;
    }

    double mid = (a + b) / 2.0;
    double acc2 = acc / std::sqrt(2.0);

    return integrate(func, a, mid, acc2, eps, f1, f2) +
           integrate(func, mid, b, acc2, eps, f3, f4);
}

double erf(double z, double acc, double eps){
    if (z<0){return -erf(-z);}
    if (0<=z && z<=1){
        auto f = [](double x){return std::exp(-x*x);};
        return 2.0/std::sqrt(M_PI) * integrate(f,0,z, acc=acc, eps=eps);
    }
    else{ //(1<z)
        auto g = [&z](double t){return std::exp(-(z+(1-t)/t)*(z+(1-t)/t))/t/t;};
        return 1.0-2.0/std::sqrt(M_PI) * integrate(g,0,1, acc=acc, eps=eps);
    }   
}



// Number B
double integrate_cc_rec(const std::function<double(double)> &f, double a, double b, double acc, double eps){
    auto g = [&](double theta){
        double x = (a+b)/2 + (b-a)/2 * std::cos(theta);
        return f(x) * (b-a)/2 * std::sin(theta);
    };
    return integrate(g, 0, M_PI, acc, eps);
}




bool approx(double a, double b, double eps)
{
    return std::fabs(a - b) < eps;
}

} // namespace pp