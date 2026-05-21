cmake_minimum_required(VERSION 3.5)
project(NavalSimulationEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
    GridCoordinate.cpp
    WeatherSystem.cpp
    BattleLog.cpp
    NavalVessel.cpp
    GuidedMissileFrigate.cpp
    AttackSubmarine.cpp
    AircraftCarrier.cpp
    SimulationEngine.cpp
)

add_executable(NavalSimulation ${SOURCES})
