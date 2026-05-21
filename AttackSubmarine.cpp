#include "AttackSubmarine.h"
#include <iostream>

AttackSubmarine::AttackSubmarine(const std::string& name, const GridCoordinate& location)
    : NavalVessel(name, "Attack Submarine", 100, 15, 6.5, location), torpedoCount(6), submerged(true), sonarStrength(8) {
}

void AttackSubmarine::calculateDamage(int incomingImpact, const std::string& weaponType) {
    if (submerged && weaponType == "Missile") {
        std::cout << vesselName << " evades surface missiles while submerged." << std::endl;
        return;
    }
    int damage = incomingImpact;
    if (weaponType == "Depth Charge" || weaponType == "Torpedo") {
        if (submerged) {
            damage = static_cast<int>(damage * 0.75);
        }
    }
    takeDamage(damage);
}

void AttackSubmarine::processTurnAction(NavalVessel* enemyTarget) {
    if (!enemyTarget || enemyTarget->isNeutralized()) {
        return;
    }
    detectTarget();
    if (submerged) {
        std::cout << vesselName << " remains submerged and prepares a torpedo attack." << std::endl;
    }
    double distance = position.distanceTo(enemyTarget->getPosition());
    if (torpedoCount > 0 && distance <= 7.0) {
        torpedoCount--;
        enemyTarget->updateStateBasedOnDetection(true);
        enemyTarget->calculateDamage(getAttackPower(), getWeaponType());
    } else if (distance > 7.0) {
        std::cout << vesselName << " is too far for torpedo range." << std::endl;
    } else {
        std::cout << vesselName << " has no torpedoes left." << std::endl;
    }
}

int AttackSubmarine::getAttackPower() const {
    return 42;
}

std::string AttackSubmarine::getWeaponType() const {
    return submerged ? "Torpedo" : "Missile";
}

void AttackSubmarine::surface() {
    submerged = false;
}

bool AttackSubmarine::isSubmerged() const {
    return submerged;
}
