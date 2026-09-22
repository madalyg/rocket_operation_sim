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

        // Advance the rocket forward by dt second(s)
        void step_rk4(Spacecraft& vehicle, double dt) const;

};