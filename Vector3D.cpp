#include "Vector3D.hpp"
#include <cmath>

Vector3D::Vector3D() : x(0.0), y(0.0), z(0.0) {}
Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}

Vector3D Vector3D::operator+(const Vector3D& other) const {
    return Vector3D(x + other.x, y + other.y, z + other.z);
}

Vector3D Vector3D::operator-(const Vector3D& other) const {
    return Vector3D(x - other.x, y - other.y, z - other.z);
}

Vector3D Vector3D::operator*(double scalar) const {
    return Vector3D(x * scalar, y * scalar, z * scalar);
}

double Vector3D::dot(const Vector3D& other) const {
    return (x * other.x) + (y * other.y) + (z * other.z);
}

Vector3D Vector3D::cross(const Vector3D& other) const { //Returns a cross product vector perpendicular to input vectors
    return Vector3D(
        y * other.z - z * other.y,
        z * other.x - x * other.z,
        x * other.y - y * other.x
    );
}

double Vector3D::magnitude() const {
    return std::sqrt(dot(*this));
}

Vector3D Vector3D::normalize() const {
    double mag = magnitude();
    if (mag > 1e-9) {
        return *this * (1.0 / mag);
    }
    return Vector3D(0.0, 0.0, 0.0);
}