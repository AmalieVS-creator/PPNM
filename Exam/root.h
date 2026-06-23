#pragma once
#include "matrix.h"
#include "QR.h"

pp::matrix jacobian(std::function<pp::vector(pp::vector)> f, pp::vector x, pp::vector fx);

pp::vector newton(std::function<pp::vector(pp::vector)> f, pp::vector x, double acc=0.01, double alpha_min=0.001, int max_iter=1000);

double newton1d(std::function<double(double)> f, double x);
