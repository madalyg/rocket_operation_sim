/**
 * @file test_validation.cpp
 * @brief Compare RK4 trajectory to closed-form constant-gravity kinematics (throttle off).
 */

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cmath>

#include "Environment.hpp"
#include "Spacecraft.hpp"

namespace {

constexpr double G = 9.80665;

void integrate_for_duration(Environment& env, Spacecraft& vehicle, double dt, double duration) {
    const int steps = static_cast<int>(std::lround(duration / dt));
    for (int i = 0; i < steps; ++i) {
        env.step_rk4(vehicle, dt);
    }
}

Spacecraft make_inert_vehicle() {
    // Dry mass only; no fuel burn when throttle is zero.
    return Spacecraft(1000.0, 0.0, 1.0e6, 0.40, 283.0);
}

}  // namespace

TEST_CASE("Projectile motion matches closed-form solution (RK4, throttle off)", "[validation][projectile]") {
    Environment env;
    Spacecraft vehicle = make_inert_vehicle();
    vehicle.set_state(Vector3D(0.0, 1500.0, 0.0), Vector3D(0.0, -50.0, 0.0));
    vehicle.command_thruster(0.0, Vector3D(0.0, 1.0, 0.0));

    const double dt = 0.05;
    const double T = 5.0;
    integrate_for_duration(env, vehicle, dt, T);

    const double ay = -G;
    const double expected_y = 1500.0 + (-50.0) * T + 0.5 * ay * T * T;
    const double expected_vy = -50.0 + ay * T;

    REQUIRE(std::abs(vehicle.get_position().y - expected_y) < 1e-6);
    REQUIRE(std::abs(vehicle.get_velocity().y - expected_vy) < 1e-6);
}
