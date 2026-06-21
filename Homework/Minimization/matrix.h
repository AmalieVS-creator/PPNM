#pragma once
#include <iostream>
#include <cstdio>
#include <iomanip>
#include <cmath>
#include <string>
#include <vector>
#include <initializer_list>
#include <functional>
#include <stdexcept>

namespace pp {

// ===================== VECTOR =====================

struct vector {
    std::vector<double> data;

    vector() = default;
    vector(int n) : data(n) {}
    vector(std::initializer_list<double> list) : data(list) {}

    vector(const vector&) = default;
    vector(vector&&) noexcept = default;

    vector& operator=(const vector&) = default;
    vector& operator=(vector&&) noexcept = default;

    size_t size() const { return data.size(); }

    void resize(int n) { data.resize(n); }

    double& operator[](int i) { return data[i]; }
    const double& operator[](int i) const { return data[i]; }

    vector& operator+=(const vector& other) {
        for (size_t i = 0; i < size(); i++) data[i] += other[i];
        return *this;
    }

    vector& operator-=(const vector& other) {
        for (size_t i = 0; i < size(); i++) data[i] -= other[i];
        return *this;
    }

    vector& operator*=(double c) {
        for (size_t i = 0; i < size(); i++) data[i] *= c;
        return *this;
    }

    vector& operator/=(double c) {
        for (size_t i = 0; i < size(); i++) data[i] /= c;
        return *this;
    }

    double norm() const {
        double sum2 = 0;
        for (size_t i = 0; i < size(); i++)
            sum2 += data[i] * data[i];
        return std::sqrt(sum2);
    }

    void print(const std::string& s = "") const {
        std::cout << s << " ";
        for (auto& x : data) std::cout << x << " ";
        std::cout << "\n";
    }

    vector map(std::function<double(double)> f) const {
        vector r(size());
        for (size_t i = 0; i < size(); i++)
            r.data[i] = f(data[i]);
        return r;
    }
};

// ===================== OPERATORS =====================

inline vector operator+(vector a, const vector& b) { a += b; return a; }
inline vector operator-(vector a) { a *= -1; return a; }
inline vector operator-(vector a, const vector& b) { a -= b; return a; }
inline vector operator*(vector a, double c) { a *= c; return a; }
inline vector operator*(double c, vector a) { a *= c; return a; }
inline vector operator/(vector a, double c) { a /= c; return a; }

inline double dot(const vector& a, const vector& b) {
    double sum = 0;
    for (size_t i = 0; i < a.size(); i++)
        sum += a[i] * b[i];
    return sum;
}

// ===================== APPROX =====================

inline bool approx(double x, double y,
                   double acc = 1e-6,
                   double eps = 1e-6) {
    if (std::abs(x - y) < acc) return true;
    if (std::abs(x - y) < eps * std::max(std::abs(x), std::abs(y))) return true;
    return false;
}

inline bool approx(const vector& a, const vector& b,
                   double acc = 1e-6,
                   double eps = 1e-6) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); i++)
        if (!approx(a[i], b[i], acc, eps)) return false;
    return true;
}

// ===================== MATRIX =====================

struct matrix {
    std::vector<vector> cols;

    matrix() = default;
    matrix(int n, int m) : cols(m, vector(n)) {}

    matrix(const matrix&) = default;
    matrix(matrix&&) noexcept = default;

    matrix& operator=(const matrix&) = default;
    matrix& operator=(matrix&&) noexcept = default;

    size_t size1() const { return cols.empty() ? 0 : cols[0].size(); }
    size_t size2() const { return cols.size(); }

    // element access
    double& operator()(int i, int j) { return cols[j][i]; }
    const double& operator()(int i, int j) const { return cols[j][i]; }

    vector& operator[](int j) { return cols[j]; }
    const vector& operator[](int j) const { return cols[j]; }

    void setid() {
        if (size1() != size2())
            throw std::runtime_error("non-square matrix");

        for (size_t i = 0; i < size1(); i++) {
            (*this)(i, i) = 1.0;
            for (size_t j = 0; j < size1(); j++) {
                if (i != j) (*this)(i, j) = 0.0;
            }
        }
    }

    void threshold(double tol = 1e-7) {
        for (size_t i = 0; i < size1(); i++) {
            for (size_t j = 0; j < size2(); j++) {
                if (std::abs((*this)(i, j)) < tol)
                    (*this)(i, j) = 0.0;
            }
        }
    }

    matrix transpose() const {
        matrix R(size2(), size1());
        for (size_t i = 0; i < size1(); i++)
            for (size_t j = 0; j < size2(); j++)
                R(j, i) = (*this)(i, j);
        return R;
    }

    void print(const std::string& s = "") const {
        std::printf("%s\n", s.c_str());
        for (size_t i = 0; i < size1(); i++) {
            for (size_t j = 0; j < size2(); j++)
                std::printf("%10.5g ", (*this)(i, j));
            std::printf("\n");
        }
    }
};

// ===================== MATRIX OPERATORS =====================

inline matrix operator+(matrix A, const matrix& B) {
    for (size_t i = 0; i < A.size2(); i++) A[i] += B[i];
    return A;
}

inline matrix operator-(matrix A, const matrix& B) {
    for (size_t i = 0; i < A.size2(); i++) A[i] -= B[i];
    return A;
}

inline matrix operator*(const matrix& A, const matrix& B) {
    if (A.size2() != B.size1())
        throw std::invalid_argument("size mismatch");

    matrix R(A.size1(), B.size2());

    for (size_t k = 0; k < A.size2(); k++) {
        for (size_t j = 0; j < B.size2(); j++) {
            double Bkj = B(k, j);
            for (size_t i = 0; i < A.size1(); i++)
                R(i, j) += A(i, k) * Bkj;
        }
    }
    return R;
}

inline matrix operator*(matrix A, double c) {
    for (auto& col : A.cols) col *= c;
    return A;
}

inline matrix operator*(double c, matrix A) {
    for (auto& col : A.cols) col *= c;
    return A;
}

inline matrix operator/(matrix A, double c) {
    for (auto& col : A.cols) col /= c;
    return A;
}

inline vector operator*(const matrix& A, const vector& v) {
    vector r(A.size1());

    for (size_t j = 0; j < A.size2(); j++) {
        double vj = v[j];
        for (size_t i = 0; i < A.size1(); i++)
            r[i] += A(i, j) * vj;
    }
    return r;
}

} // namespace pp