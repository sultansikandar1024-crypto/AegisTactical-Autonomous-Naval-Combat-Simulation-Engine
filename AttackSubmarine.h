#ifndef ATTACKSUBMARINE_H
#define ATTACKSUBMARINE_H

#include "NavalVessel.h"

class AttackSubmarine : public NavalVessel {
private:
    int torpedoCount;
    bool submerged;
    int sonarStrength;

public:
    AttackSubmarine(const std::string& name, const GridCoordinate& location);
    void calculateDamage(int incomingImpact, const std::string& weaponType) override;
    void processTurnAction(NavalVessel* enemyTarget) override;
    int getAttackPower() const override;
    std::string getWeaponType() const override;
    void surface();
    bool isSubmerged() const;
};

#endif // ATTACKSUBMARINE_H
