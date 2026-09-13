 //Madaly G 2026
/**
 * @file Spacecraft.cpp
 * @brief Rocket vehicle state properties and variable mass propulsion system.
 * 
 * @reference Bate, R. R., Mueller, D. D., & White, J. E. (1971). 
 *            "Fundamentals of Astrodynamics", Dover Publications. Ch. 1 (Rocket Equation).
 * @reference Niskanen, S. (2013). "OpenRocket Technical Documentation", 
 *            Section 3.2: Thrust Vectoring & Throttle Constraints.
 */

#pragma once
#include "Vector3D.hpp"

class Spacecraft {
    private:
        //Kinematic state vectors
        Vector3D position; //meters (m) relative to the landing pad
        Vector3D velocity; //(m/s)
        Vector3D acceleration; //(m/s^2)

        //Mass properties
        double dry_mass; //kg (mass without fuel)
        double fuel_mass; //kg

        //Propulsion system properties
        double max_thrust; //(N)
        double min_throttle; //0.0 to 1.0 (percentage of max thrust)
        double isp; //(s) specific impulse, efficiency of the engine

        //Actuator state
        double current_throttle; //0.0 to 1.0
        Vector3D thrust_direction; //Normalized direction vector

    public:
        //Constructor
        Spacecraft(double dry_mass, double fuel_mass, double max_thrust, double min_throttle, double isp);

        //Getters
        Vector3D get_position() const { return position; }
        Vector3D get_velocity() const { return velocity; }
        Vector3D get_acceleration() const { return acceleration; }
        double get_total_mass() const { return dry_mass + fuel_mass; }
        double get_fuel_mass() const { return fuel_mass; }

        //Setters
        void set_state(const Vector3D& pos, const Vector3D& vel);

        //Flight commands
        void command_thruster(double throttle_request, const Vector3D& direction_request); //Return the throttle and direction to the propulsion system

        //Physics update commands
        Vector3D calculate_thrust_force() const;
        void update_mass(double dt);
        void update_kinematics(const Vector3D& next_pos, const Vector3D& next_vel, const Vector3D& next_accel);
};
