//Madaly G 2026
/**
 * @file main.cpp
 * @brief Main execution file for the rocket operation simulator.
 * @reference Wie, B. (1998). "Space Vehicle Dynamics and Control", AIAA. Ch. 2.
 * @reference NASA-SP-8008: "Pre-launch Dynamic Loads Analysis".
 */

#include <iostream>
#include "Vector3D.hpp"

int main() {
    std::cout << "========================================" << std::endl;
    std::cout << " Rocket Operation Simulator Booting... " << std::endl;
    std::cout << " OS: Linux (Docker)        " << std::endl;
    std::cout << "========================================" << std::endl;
    //Define an arbitrary rocket position and a gravity vector
    Vector3D rocket_position(0.0, 5000.0, 0.0); //5000 meters altitude
    Vector3D gravity(0.0, -9.81, 0.0);          //Acceleration vector m/s^2

    std::cout << "Initial Rocket Altitude: " << rocket_position.y << " meters." << std::endl;
    std::cout << "Gravity Vector Magnitude: " << gravity.magnitude() << " m/s^2." << std::endl;

    return 0;
}
