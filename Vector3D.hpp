/**
 * @file Vector3D.hpp
 * @brief 3D vector definition used for spacecraft kinematics and forces.
 * @author Madaly G
 * @date 2026-09-06
 */

#pragma once //Include header only once in file

class Vector3D {
public:
    double x, y, z;

    //Constructors
    Vector3D();
    Vector3D(double x, double y, double z);

    //Main vector math operations req. for GNC physics
    Vector3D operator+(const Vector3D& other) const;
    Vector3D operator-(const Vector3D& other) const;
    Vector3D operator*(double scalar) const; //Scaling forces
    
    double dot(const Vector3D& other) const;
    Vector3D cross(const Vector3D& other) const;
    double magnitude() const;
    Vector3D normalize() const;
};