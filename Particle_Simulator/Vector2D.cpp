#include "Vector2D.hpp"

Vector2D::Vector2D() : x(0.0), y(0.0) {}
Vector2D::Vector2D(double xVal, double yVal) : x(xVal), y(yVal) {}

// Vector operations
double Vector2D::modulus() const {
    return sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize() const {
    double mod = modulus();
    if (mod != 0.0) {
        return Vector2D(x / mod, y / mod);
    }
    else {
        return *this;
    }
}

// Operator overloads
Vector2D Vector2D::operator+(const Vector2D& other) const {
    return Vector2D(x + other.x, y + other.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other) {
    x += other.x;
    y += other.y;
    return *this; // Return the modified object by reference
}

Vector2D Vector2D::operator-(const Vector2D& other) const {
    return Vector2D(x - other.x, y - other.y);
}

Vector2D& Vector2D::operator-=(const Vector2D& other) {
    x -= other.x;
    y -= other.y;
    return *this; // Return the modified object by reference
}

double Vector2D::operator*(const Vector2D& other) const {
    // Dot product
    return x * other.x + y * other.y;
}

Vector2D Vector2D::operator*(const double& other) const {
    return Vector2D(x * other, y * other);
}

Vector2D Vector2D::operator/(const double& other) const {
    return Vector2D(x / other, y / other);
}

// Print method
std::ostream& operator<<(std::ostream& os, const Vector2D& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}