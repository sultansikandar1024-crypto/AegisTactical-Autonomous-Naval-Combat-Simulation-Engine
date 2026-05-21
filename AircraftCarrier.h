#ifndef AIRCRAFTCARRIER_H
#define AIRCRAFTCARRIER_H

#include "NavalVessel.h"

class AircraftCarrier : public NavalVessel {
private:
    int fighterSquadrons;
    bool interceptorReady;
    int flightDeckIntegrity;

public:
    AircraftCarrier(const std::string& name, const GridCoordinate& location);
    void calculateDamage(int incomingImpact, const std::string& weaponType) override;
    void processTurnAction(NavalVessel* enemyTarget) override;
    int getAttackPower() const override;
    std::string getWeaponType() const override;
    void deployInterceptors();
    bool hasInterceptorCover() const;
};

#endif // AIRCRAFTCARRIER_H
