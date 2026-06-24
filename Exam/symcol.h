#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <random>
#include "root.h"
#include "evd.h"



// Secular function and derivative for one lambda
static void secular_one(const std::vector<double>& d,
                         const std::vector<double>& u,
                         int p,
                         double lambda,
                         double& f,
                         double& df);

static pp::vector compute_eigenvector(const std::vector<double>& d,
                                       const std::vector<double>& u,
                                       int p,
                                       double lambda);





std::pair<std::vector<double>, std::vector<pp::vector>> eigen_rank2_update(std::vector<double> d_in,
                                        std::vector<double> u_in,
                                        int p);


pp::matrix build_A(const std::vector<double>& d,
                   const std::vector<double>& u,
                   int p);


void verify_eigenvectors(const std::vector<double>& d,
                          const std::vector<double>& u,
                          int p,
                          const std::vector<double>& eigenvalues,
                          const std::vector<pp::vector>& eigenvectors);