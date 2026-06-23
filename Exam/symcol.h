#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#include "matrix.h"
#include "QR.h"
#include "root.h"

using namespace pp;


double secular(double lambda,
               const pp::vector& d,
               const pp::vector& u,
               int p);

double solve_root(const pp::vector& d,
                  const pp::vector& u,
                  int p,
                  double left,
                  double right);

pp::vector fast_eigenvalues(const pp::vector& d,
                             const pp::vector& u,
                             int p);

pp::matrix build_matrix(const pp::vector& d,
                    const pp::vector& u,
                    int p);


void compare(std::vector<double> a,
             std::vector<double> b);


