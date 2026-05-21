#ifndef GUIDEDMISSILEFRIGATE_H
#define GUIDEDMISSILEFRIGATE_H

#include "NavalVessel.h"

class GuidedMissileFrigate : public NavalVessel {
private:
    int missileLauncherCount;
    bool interceptorChaffReady;
    int electronicWarfareLevel;

public:
    GuidedMissileFrigate(const std::string& name, const GridCoordinate& location);
    void calculateDamage(int incomingImpact, const std::string& weaponType) override;
    void processTurnAction(NavalVessel* enemyTarget) override;
    int getAttackPower() const override;
    std::string getWeaponType() const override;
};

#endif // GUIDEDMISSILEFRIGATE_H
