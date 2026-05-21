#include "GuidedMissileFrigate.h"
#include <iostream>

GuidedMissileFrigate::GuidedMissileFrigate(const std::string& name, const GridCoordinate& location)
    : NavalVessel(name, "Guided Missile Frigate", 120, 20, 8.0, location), missileLauncherCount(4), interceptorChaffReady(true), electronicWarfareLevel(4) {
}

void GuidedMissileFrigate::calculateDamage(int incomingImpact, const std::string& weaponType) {
    int damage = incomingImpact;
    if (weaponType == "Missile" && interceptorChaffReady) {
        damage = static_cast<int>(damage * 0.65);
        interceptorChaffReady = false;
    }
    if (weaponType == "Torpedo") {
        damage = static_cast<int>(damage * 0.85);
    }
    takeDamage(damage);
}

void GuidedMissileFrigate::processTurnAction(NavalVessel* enemyTarget) {
    if (!enemyTarget || enemyTarget->isNeutralized()) {
        return;
    }
    detectTarget();
    engage();
    double distance = position.distanceTo(enemyTarget->getPosition());
    std::cout << vesselName << " launches a missile strike at " << enemyTarget->getName() << " from " << position.toString() << "." << std::endl;
    if (distance <= 8.0 && missileLauncherCount > 0) {
        missileLauncherCount--;
        enemyTarget->updateStateBasedOnDetection(true);
        enemyTarget->calculateDamage(getAttackPower(), getWeaponType());
    } else {
        std::cout << vesselName << " cannot reach " << enemyTarget->getName() << " this turn." << std::endl;
    }
}

int GuidedMissileFrigate::getAttackPower() const {
    return 35;
}

std::string GuidedMissileFrigate::getWeaponType() const {
    return "Missile";
}
