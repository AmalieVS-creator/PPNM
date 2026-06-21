#ifndef LS_H
#define LS_H

#include<vector>

namespace pp{

int binsearch(const std::vector<double>& x,double z);

double linterp(const std::vector<double>& x,
               const std::vector<double>& y,
               double z);

double linterpInteg(const std::vector<double>& x,
                    const std::vector<double>& y,
                    double z);

/* ------------ Quadratic spline ---------------- */

class qspline{
private:
    std::vector<double> x,y,b,c;

public:
    qspline(const std::vector<double>& xs,
            const std::vector<double>& ys);

    double eval(double z) const;

    double deriv(double z) const;

    double integ(double z) const;
};

}

#endif