// vec.h
#pragma once
#include <iostream>
#include <cmath>
#include <string>

namespace pp {

template<typename T>
struct vec {
    T x, y, z;

    // constructors
    vec(T x, T y, T z) : x(x), y(y), z(z) {}
    vec() : vec(0, 0, 0) {}

    vec(const vec&) = default;
    vec(vec&&) = default;
    ~vec() = default;

    // assignment
    vec& operator=(const vec&) = default;
    vec& operator=(vec&&) = default;

    // arithmetic
    vec& operator+=(const vec& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }

    vec& operator-=(const vec& other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }

    vec& operator*=(T n) {
        x *= n;
        y *= n;
        z *= n;
        return *this;
    }

    vec& operator/=(T n) {
        x /= n;
        y /= n;
        z /= n;
        return *this;
    }

    // utility
    void set(T a, T b, T c) {
        x = a;
        y = b;
        z = c;
    }

    void print(const std::string& s = "") const {
        std::cout << s << x << " " << y << " " << z << std::endl;
    }
};

// stream output
template<typename T>
std::ostream& operator<<(std::ostream& os, const vec<T>& v) {
    os << "{ " << v.x << ", " << v.y << ", " << v.z << " }";
    return os;
}

// unary minus
template<typename T>
vec<T> operator-(const vec<T>& a) {
    return vec<T>(-a.x, -a.y, -a.z);
}

// addition
template<typename T>
vec<T> operator+(const vec<T>& a, const vec<T>& b) {
    vec<T> r = a;
    r += b;
    return r;
}

// subtraction
template<typename T>
vec<T> operator-(const vec<T>& a, const vec<T>& b) {
    vec<T> r = a;
    r -= b;
    return r;
}

// scalar multiplication
template<typename T>
vec<T> operator*(const vec<T>& a, T n) {
    vec<T> r = a;
    r *= n;
    return r;
}

template<typename T>
vec<T> operator*(T n, const vec<T>& a) {
    return a * n;
}

// scalar division
template<typename T>
vec<T> operator/(const vec<T>& a, T n) {
    vec<T> r = a;
    r /= n;
    return r;
}

// dot product
template<typename T>
T dot(const vec<T>& a, const vec<T>& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// cross product
template<typename T>
vec<T> cross(const vec<T>& a, const vec<T>& b) {
    return vec<T>(
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    );
}

// norm
template<typename T>
T norm(const vec<T>& a) {
    return std::sqrt(dot(a, a));
}

// approximate equality for scalars
template<typename T>
bool approx(T a, T b, T acc = 1e-6, T eps = 1e-6) {
    if(std::fabs(a - b) < acc) return true;
    if(std::fabs(a - b) < eps * (std::fabs(a) + std::fabs(b))) return true;
    return false;
}

// approximate equality for vectors
template<typename T>
bool approx(const vec<T>& u, const vec<T>& v,
            T acc = 1e-6, T eps = 1e-6) {
    return
        approx(u.x, v.x, acc, eps) &&
        approx(u.y, v.y, acc, eps) &&
        approx(u.z, v.z, acc, eps);
}

} // namespace pp