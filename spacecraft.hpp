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
};


