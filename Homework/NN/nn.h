#pragma once

#include <functional>
#include "matrix.h"

struct ann
{
    int n;
    std::function<double(double)> f;
    pp::vector p;

    ann(int n_);

    double response(double x);

    void train(const pp::vector& x, const pp::vector& y);

    double derivative(double x);
    double second_derivative(double x);
    double antiderivative(double x);
};