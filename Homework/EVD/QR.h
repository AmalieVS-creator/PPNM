#pragma once
#include "matrix.h"


namespace pp {

struct QR {
    pp::matrix Q;
    pp::matrix R;

    QR(const pp::matrix& A);

    pp::vector solve(const pp::vector& b) const;

    double det();

    pp::matrix inverse() const;
};

}