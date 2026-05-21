# Autonomous Tactical Naval Battle Simulation Engine

This project implements a modular C++ command-line simulation engine for tactical naval combat. It is written in standard C++11 and uses a clean multi-file OOP architecture.

## Project Structure

- `main.cpp` - Entry point for the simulation.
- `SimulationEngine.h` / `SimulationEngine.cpp` - Central controller loop and battle management.
- `NavalVessel.h` / `NavalVessel.cpp` - Abstract base class for combat vessels.
- `GuidedMissileFrigate.h` / `GuidedMissileFrigate.cpp` - Missile frigate implementation.
- `AttackSubmarine.h` / `AttackSubmarine.cpp` - Submarine implementation with deep-water evasion.
- `AircraftCarrier.h` / `AircraftCarrier.cpp` - Carrier implementation with interceptor logic.
- `WeatherSystem.h` / `WeatherSystem.cpp` - Dynamic environmental modifiers.
- `BattleLog.h` / `BattleLog.cpp` - Structured console logging.
- `GridCoordinate.h` / `GridCoordinate.cpp` - 3D coordinate and boundary validation.

## Build Instructions

### Using CMake

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

### Direct compile with GCC / Clang

```bash
g++ -std=c++11 main.cpp GridCoordinate.cpp WeatherSystem.cpp BattleLog.cpp NavalVessel.cpp GuidedMissileFrigate.cpp AttackSubmarine.cpp AircraftCarrier.cpp SimulationEngine.cpp -o NavalSimulation.exe
```

### Direct compile with MSVC

Open a "Developer Command Prompt for VS" and run:

```bat
cl /EHsc /std:c++11 main.cpp GridCoordinate.cpp WeatherSystem.cpp BattleLog.cpp NavalVessel.cpp GuidedMissileFrigate.cpp AttackSubmarine.cpp AircraftCarrier.cpp SimulationEngine.cpp
```

## Run

```bash
./NavalSimulation.exe
```

## Repository Integration

This project is ready to be added to a GitHub repository.

Remote repository URL:

```text
https://github.com/sultansikandar1024-crypto/AegisTactical-Autonomous-Naval-Combat-Simulation-Engine.git
```

### Recommended Git steps

```bash
git init
git add .
git commit -m "Add naval battle simulation engine"
git remote add origin https://github.com/sultansikandar1024-crypto/AegisTactical-Autonomous-Naval-Combat-Simulation-Engine.git
git push -u origin main
```

> Note: Git is not currently available in the host environment, so these commands must be run after installing Git or using a developer terminal where Git is configured.
