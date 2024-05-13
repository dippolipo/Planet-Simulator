#pragma once
#include <iostream>

class Vector2D {
public:
    long double x;
    long double y;
    Vector2D();
    Vector2D(double xVal, double yVal);
    double modulus() const;
    Vector2D normalize() const;
    Vector2D operator+(const Vector2D& other) const;
    Vector2D& operator+=(const Vector2D& other);
    Vector2D operator-(const Vector2D& other) const;
    Vector2D& operator-=(const Vector2D& other);
    double operator*(const Vector2D& other) const;
    Vector2D operator*(const double& other) const;
    Vector2D operator/(const double& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Vector2D& vec);
};