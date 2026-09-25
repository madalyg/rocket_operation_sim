/**
 * @file Environment.hpp
 * @brief Models the gravitational field and other environmental effects on the spacecraft.
 * @author Madaly G
 * @date 2026-09-22
 *
 * @reference Vallado, D. A. (2013). Fundamentals of Astrodynamics and Applications
 *            (4th ed.). Microcosm Press.
 */

#pragma once
#include "Vector3D.hpp"
#include "Spacecraft.hpp"

class Environment {
    private:
        Vector3D gravity_vector; // Acceleration due to gravity in m/s^2
        
        // Hold instantaneous derivative states for the RK4 step calculations
        struct Derivative {
            Vector3D velocity; // Velocity vector in m/s
            Vector3D acceleration; // Acceleration vector in m/s^2
        };

        // Calculate instantaneous acceleration based on current position and velocity
        Vector3D compute_acceleration(const Spacecraft& vehicle, const Vector3D& pos, const Vector3D& vel) const;

    public:
        Environment(const Vector3D& gravity = Vector3D(0.0, -9.80665, 0.0)); // Default gravity vector pointing downwards

        // Advance the rocket forward by dt second(s) using RK4 integration
        void step_rk4(Spacecraft& vehicle, double dt) const; //

};