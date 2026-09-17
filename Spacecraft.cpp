/// Madaly G 2026
/**
 * @file Spacecraft.cpp
 * @brief Implementation of the Spacecraft class. Uses the dynamic constraints of a rocket,
 *       including variable fuel mass depletion rate and thrust direction.
 */

#include "Spacecraft.hpp"
#include <algorithm> // For std::clamp
#include <iostream>

const double G0 = 9.80665; // Earth gravity constant in m/s^2

Spacecraft::Spacecraft(double dry_mass, double initial_fuel, double max_thrust, double min_throttle, double isp)
    : dry_mass(dry_mass), fuel_mass(initial_fuel), max_thrust(max_thrust), min_throttle(min_throttle), isp(isp),
      current_throttle(0,0), thrust_direction(Vector3D(0, 1, 0)) {}

//Call setters
void Spacecraft::set_state(const Vector3D& pos, Vector3D& vel) {
    position = pos;
    velocity = vel;
    acceleration = Vector3D(0, 0, 0);
}

//Call flight commands
void Spacecraft::command_thruster(double throttle_request, const Vector3D& direction_request) {
    if (fuel_mass <= 1e-3) {
        current_throttle = 0.0;
        thrust_direction = Vector3D(0, 0, 0); //Conserve fuel if fuel mass is below 1 gram threshold by setting thrust to zero
        return;
    }

    if (throttle_request > 0.0) {
        current_throttle = std::clamp(throttle_request, min_throttle, 1.0);
    } else {
        current_throttle = 0.0;
    }

    thrust_direction = direction_request.normalize();
}