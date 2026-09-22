/**
 * @file Main.cpp
 * @brief Main execution file for the rocket operation simulator.
 * @author Madaly G
 * @date 2026-09-06
 * @reference Wie, B. (1998). "Space Vehicle Dynamics and Control", AIAA. Ch. 2.
 * @reference NASA-SP-8008: "Pre-launch Dynamic Loads Analysis".
 * @reference National Aeronautics and Space Administration Wiki. (n.d.). Falcon 9. https://nasa.fandom.com/wiki/Falcon_9#Specifications
 */

#include <iostream>
#include "Vector3D.hpp"
#include "Spacecraft.hpp"

int main() {
    {/* std::cout << "========================================" << std::endl;
    std::cout << " Rocket Operation Simulator Booting... " << std::endl;
    std::cout << " OS: Linux (Docker)        " << std::endl;
    std::cout << "========================================" << std::endl;
    //Define an arbitrary rocket position and a gravity vector
    Vector3D rocket_position(0.0, 5000.0, 0.0); //5000 meters altitude
    Vector3D gravity(0.0, -9.81, 0.0);          //Acceleration vector m/s^2

    std::cout << "Initial Rocket Altitude: " << rocket_position.y << " meters." << std::endl;
    std::cout << "Gravity Vector Magnitude: " << gravity.magnitude() << " m/s^2." << std::endl;

    return 0; */}

    std::cout << "==================State Properties Verification Active ======================" << std::endl;
    // Instantiate rocket: dry mass=25,600kg, fuel=15,000kg, max thrust=845,222N, min throttle=0.40, isp=283s
    Spacecraft rocket(25600.0, 15000.0, 845222.0, 0.40, 283.0);

    // Set initial kinematic state vectors: 1500m up, falling at 50 m/s
    rocket.set_state(Vector3D(0.0, 1500.0, 0.0), Vector3D(0.0, -50.0, 0.0));

    std::cout << "Initial Liftoff Mass: " << rocket.get_total_mass() << " kg" << std::endl;

    // Example flight computer command: fire thrust 100% straight up
    rocket.command_thruster(1.0, Vector3D(0, 1, 0));

    Vector3D thrust = rocket.calculate_thrust_force();
    std::cout << "Engine Thrust Output: " << thrust.y << " Newtons" << std::endl;

    // Burn enfine for 10 s to simulate fuel consumption
    double dt = 1.0; // 1 s timestep
    for (int step = 1; step <= 10; step++) {
        rocket.update_mass(dt);
    }
    std::cout << "Remaining Fuel Mass after 10s burn: " << rocket.get_fuel_mass() << " kg" << std::endl;
    std::cout << "Total Vehicle Mass After 10s burn:" << rocket.get_total_mass() << " kg" << std::endl;

    return 0;
}
