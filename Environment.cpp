/**
 * @file Environment.cpp
 * @brief Implementation of the Environment class. Models the gravitational field on the spacecraft.
 * @author Madaly G
 * @date 2026-09-23
 */

#include Environment.hpp

Enviornment::Environment(const Vector3D& gravity) : gravity_vector(gravity) {}

Vector3D Environment::compute_acceleration(const Spacecraft& vehicle, const Vector3D& pos, Vector3D& vel) const {
    // Total acceleration is the sum of the gravity vector and thrust force vector / mass, from f=ma
    double mass = vehicle.get_total_mass();
    if (mass <= 0.0) return gravity_vector;
    
    Vector3D thrust_force = vehicle.get.calculate_thrust_force();
    return gravity_vector + (thrust_force * (1.0 / mass));
}

void Environment::step_rk4(Spacecraft& vehicle, double dt) const {
    // Get the current state of the spacecraft
    Vector3D x0 = vehicle.get_position();
    Vector3d v0 = vehicle.get_velocity();

    // k1: evaluate derivatives at the initial state
    Derivative k1;
    k1.velocity = v0;
    k1.acceleration = compute_acceleration(vehicle, x0, v0);

    //k2: evaluate derivatives at the midpoint using values from k1
    Vector3D x1 = x0 + k1.velocity * (dt * 0.5);
    Vector3D v1 = v0 + k1.acceleration * (dt * 0.5);
    Derivative k2;
    k2.velocity = v1;
    k2.acceleration = compute_acceleration(vehicle, x1, v1);

    // k3: evaluate derivatives at the midpoint using values from k2
    Vector3D x2 = x0 + k2.velocity * (dt * 0.5);
    Vector3D v2 = v0 + k2.acceleration * (dt * 0.5);
    Derivative k3;
    k3.velocity = v2;
    k3.acceleration = compute_acceleration(vehicle, x2, v2);

    // k4: evaluate derivatives at the endpoint using values from k3
    Vector3D x3 = x0 + k3.velocity * dt;
    Vector3D v3 = v0 + k3.acceleration * dt;
    Derivative k4;
    k4.velocity = v3;
    k4.acceleration = compute_acceleration(vehicle, x3, v3);

    // Weighted average update of position and velocity states
    Vector3D final_pos = x0 + (k1.velocity + k2.velocity * 2.0 + k3.velocity * 2.0 + k4.velocity) * (dt / 6.0);
    Vector3D final_vel = v0 + (k1.acceleration + k2.acceleration * 2.0 + k3.acceleration * 2.0 + k4.acceleration) * (dt / 6.0);

    // Update the acceleration state of the spacecraft
    Vector3D final_accel = compute_acceleration(vehicle, final_pos, final_vel);

    // Commit physical updates to the spacecraft
    vehicle.update_mass(dt); // Update mass based on fuel consumption
    vehicle.update_kinematics(final_pos, final_vel, final_accel);

}

