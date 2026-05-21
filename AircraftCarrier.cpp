#include "AircraftCarrier.h"
#include <iostream>

AircraftCarrier::AircraftCarrier(const std::string& name, const GridCoordinate& location)
    : NavalVessel(name, "Aircraft Carrier", 160, 25, 5.0, location), fighterSquadrons(3), interceptorReady(true), flightDeckIntegrity(90) {
}

void AircraftCarrier::calculateDamage(int incomingImpact, const std::string& weaponType) {
    int damage = incomingImpact;
    if (weaponType == "Missile" && interceptorReady) {
        damage = static_cast<int>(damage * 0.65);
    }
    if (weaponType == "Missile" && !interceptorReady) {
        damage = static_cast<int>(damage * 1.3);
    }
    if (weaponType == "Torpedo") {
        damage = static_cast<int>(damage * 1.2);
    }
    flightDeckIntegrity -= damage / 2;
    if (flightDeckIntegrity < 0) {
        flightDeckIntegrity = 0;
    }
    takeDamage(damage);
    if (flightDeckIntegrity < 25) {
        interceptorReady = false;
    }
}

void AircraftCarrier::processTurnAction(NavalVessel* enemyTarget) {
    if (!enemyTarget || enemyTarget->isNeutralized()) {
        return;
    }
    detectTarget();
    deployInterceptors();
    double distance = position.distanceTo(enemyTarget->getPosition());
    std::cout << vesselName << " launches carrier-based strike against " << enemyTarget->getName() << "." << std::endl;
    if (distance <= 8.5) {
        enemyTarget->updateStateBasedOnDetection(true);
        enemyTarget->calculateDamage(getAttackPower(), getWeaponType());
    } else {
        std::cout << "Target is out of range for " << vesselName << "." << std::endl;
    }
}

int AircraftCarrier::getAttackPower() const {
    return 30;
}

std::string AircraftCarrier::getWeaponType() const {
    return "Air Strike";
}

void AircraftCarrier::deployInterceptors() {
    if (fighterSquadrons > 0) {
        interceptorReady = true;
    }
}

bool AircraftCarrier::hasInterceptorCover() const {
    return interceptorReady && fighterSquadrons > 0;
}
