#include "SimulationEngine.h"
#include "GuidedMissileFrigate.h"
#include "AttackSubmarine.h"
#include "AircraftCarrier.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

SimulationEngine::SimulationEngine()
    : turnCounter(0), simulationActive(false) {
}

void SimulationEngine::initializeSimulation() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    battleLog.logEvent("Initializing Autonomous Tactical Naval Battle Simulation Engine.");
    buildFleetA();
    buildFleetB();
    assignFleets();
    simulationActive = true;
    processWeather();
    battleLog.logWeatherUpdate(weather.generateSummary());
}

void SimulationEngine::buildFleetA() {
    allVessels.emplace_back(new GuidedMissileFrigate("Frigate Alpha", GridCoordinate(2, 3, 0)));
    allVessels.emplace_back(new AttackSubmarine("Submarine Alpha", GridCoordinate(1, 5, -1)));
    allVessels.emplace_back(new AircraftCarrier("Carrier Alpha", GridCoordinate(0, 2, 0)));
}

void SimulationEngine::buildFleetB() {
    allVessels.emplace_back(new GuidedMissileFrigate("Frigate Bravo", GridCoordinate(7, 6, 0)));
    allVessels.emplace_back(new AttackSubmarine("Submarine Bravo", GridCoordinate(8, 4, -1)));
    allVessels.emplace_back(new AircraftCarrier("Carrier Bravo", GridCoordinate(9, 8, 0)));
}

void SimulationEngine::assignFleets() {
    if (allVessels.size() < 6) {
        return;
    }
    fleetA.clear();
    fleetB.clear();
    fleetA.push_back(allVessels[0].get());
    fleetA.push_back(allVessels[1].get());
    fleetA.push_back(allVessels[2].get());
    fleetB.push_back(allVessels[3].get());
    fleetB.push_back(allVessels[4].get());
    fleetB.push_back(allVessels[5].get());
}

NavalVessel* SimulationEngine::chooseTarget(NavalVessel* attacker, const std::vector<NavalVessel*>& enemyFleet) const {
    NavalVessel* closest = nullptr;
    double bestDistance = 1e9;
    for (NavalVessel* enemy : enemyFleet) {
        if (!enemy || enemy->isNeutralized()) {
            continue;
        }
        double distance = attacker->getPosition().distanceTo(enemy->getPosition());
        if (distance < bestDistance) {
            bestDistance = distance;
            closest = enemy;
        }
    }
    return closest;
}

void SimulationEngine::resolveFleetActions(std::vector<NavalVessel*>& attackers, std::vector<NavalVessel*>& defenders) {
    double visibility = static_cast<double>(weather.getVisibilityRange());
    double accuracyBase = 0.8 * weather.getAccuracyModifier();
    for (NavalVessel* attacker : attackers) {
        if (!attacker || attacker->isNeutralized()) {
            continue;
        }
        NavalVessel* target = chooseTarget(attacker, defenders);
        if (!target) {
            battleLog.logEvent(attacker->getName() + " finds no valid target.");
            continue;
        }
        double distance = attacker->getPosition().distanceTo(target->getPosition());
        if (distance > visibility) {
            battleLog.logEvent(attacker->getName() + " cannot detect " + target->getName() + " due to limited visibility.");
            continue;
        }
        double hitChance = accuracyBase - (distance * 0.03);
        if (hitChance < 0.25) {
            hitChance = 0.25;
        }
        int roll = std::rand() % 100;
        if (roll < static_cast<int>(hitChance * 100)) {
            battleLog.logEvent(attacker->getName() + " successfully executes a strike on " + target->getName() + ".");
            attacker->processTurnAction(target);
        } else {
            battleLog.logEvent(attacker->getName() + " misses the attack on " + target->getName() + ".");
        }
    }
}

bool SimulationEngine::isFleetNeutralized(const std::vector<NavalVessel*>& fleet) const {
    for (NavalVessel* vessel : fleet) {
        if (vessel && !vessel->isNeutralized()) {
            return false;
        }
    }
    return true;
}

void SimulationEngine::printBattleStatus() const {
    std::cout << "\n=== Turn " << turnCounter << " Summary ===" << std::endl;
    logFleetSummary(fleetA, "Fleet A");
    logFleetSummary(fleetB, "Fleet B");
    std::cout << weather.generateSummary() << std::endl;
}

void SimulationEngine::logFleetSummary(const std::vector<NavalVessel*>& fleet, const std::string& fleetName) const {
    std::cout << "--- " << fleetName << " ---" << std::endl;
    for (NavalVessel* vessel : fleet) {
        if (!vessel) {
            continue;
        }
        std::cout << vessel->getName() << " | Hull: " << vessel->getHullIntegrity() << " | State: " << vessel->getStateName() << " | Location: " << vessel->getPosition().toString() << std::endl;
    }
}

void SimulationEngine::processWeather() {
    weather.randomizeWeather();
}

void SimulationEngine::runSimulation() {
    if (!simulationActive) {
        battleLog.logEvent("Simulation engine was not initialized correctly.");
        return;
    }
    while (simulationActive && turnCounter < 25) {
        turnCounter++;
        processWeather();
        battleLog.logWeatherUpdate(weather.generateSummary());
        battleLog.logEvent("Starting turn " + std::to_string(turnCounter) + ".");
        resolveFleetActions(fleetA, fleetB);
        resolveFleetActions(fleetB, fleetA);
        printBattleStatus();
        if (isFleetNeutralized(fleetA) || isFleetNeutralized(fleetB)) {
            simulationActive = false;
            break;
        }
    }
    if (isFleetNeutralized(fleetA) && isFleetNeutralized(fleetB)) {
        battleLog.logEvent("The battle ends in a draw. Both fleets have been neutralized.");
    } else if (isFleetNeutralized(fleetA)) {
        battleLog.logEvent("Fleet B has won the battle.");
    } else if (isFleetNeutralized(fleetB)) {
        battleLog.logEvent("Fleet A has won the battle.");
    } else {
        battleLog.logEvent("Maximum turn count reached. Simulation ends with no decisive victor.");
    }
    battleLog.printRecentEvents(10);
}
