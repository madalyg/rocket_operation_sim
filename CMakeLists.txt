cmake_minimum_required(VERSION 3.14)
project(rocket_operation_sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(sim_core
    Vector3D.cpp
    Spacecraft.cpp
    Environment.cpp
)
target_include_directories(sim_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(rocket_sim Main.cpp)
target_link_libraries(rocket_sim PRIVATE sim_core)

add_executable(sim_tests tests/test_validation.cpp)
target_include_directories(sim_tests PRIVATE tests)
target_link_libraries(sim_tests PRIVATE sim_core)

enable_testing()
add_test(NAME validation COMMAND sim_tests)
