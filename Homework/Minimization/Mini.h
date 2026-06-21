#pragma once
#include "matrix.h"
#include "QR.h"

pp::vector gradient(std::function<double(const pp::vector&)> phi, pp::vector x);

pp::matrix hessian(std::function<double(const pp::vector&)> phi, pp::vector x);

std::pair<pp::vector, int> newton(std::function<double(pp::vector)> phi, pp::vector x, double acc=0.001);
    