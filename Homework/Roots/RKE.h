#pragma once
#include <vector>
#include <tuple>
#include <functional>
#include "matrix.h"

namespace pp{
std::tuple<pp::vector,pp::vector> rkstep12(
	std::function<pp::vector(double,pp::vector)> f,
	double x,
	pp::vector y,
	double h
);

std::tuple<std::vector<double>, std::vector<pp::vector>> driver(
	std::function<pp::vector(double,pp::vector)> F,
	double a,double b,
	pp::vector yinit,
	double h=0.125,
	double acc=0.01,
	double eps=0.01,
	double hmin=0
);
}