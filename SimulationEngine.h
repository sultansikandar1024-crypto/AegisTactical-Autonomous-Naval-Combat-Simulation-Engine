#ifndef SIMULATIONENGINE_H
#define SIMULATIONENGINE_H

#include "BattleLog.h"
#include "WeatherSystem.h"
#include "NavalVessel.h"
#include <memory>
#include <vector>

class SimulationEngine {
private:
    WeatherSystem weather;
    BattleLog battleLog;
    int turnCounter;
    bool simulationActive;
    std::vector<std::unique_ptr<NavalVessel>> allVessels;
    std::vector<NavalVessel*> fleetA;
    std::vector<NavalVessel*> fleetB;

    void buildFleetA();
    void buildFleetB();
    void assignFleets();
    NavalVessel* chooseTarget(NavalVessel* attacker, const std::vector<NavalVessel*>& enemyFleet) const;
    void resolveFleetActions(std::vector<NavalVessel*>& attackers, std::vector<NavalVessel*>& defenders);
    bool isFleetNeutralized(const std::vector<NavalVessel*>& fleet) const;
    void printBattleStatus() const;
    void logFleetSummary(const std::vector<NavalVessel*>& fleet, const std::string& fleetName) const;
    void processWeather();

public:
    SimulationEngine();
    void initializeSimulation();
    void runSimulation();
};

#endif // SIMULATIONENGINE_H
