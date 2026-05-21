#ifndef NAVALVESSEL_H
#define NAVALVESSEL_H

#include "GridCoordinate.h"
#include <string>

enum class VesselState {
    Stealth,
    Spotted,
    Engaged,
    Neutralized
};

class NavalVessel {
protected:
    std::string vesselName;
    std::string vesselType;
    int hullIntegrity;
    int armorRating;
    double speed;
    bool detected;
    VesselState currentState;
    GridCoordinate position;

public:
    NavalVessel(const std::string& name, const std::string& type, int hull, int armor, double speed, const GridCoordinate& location);
    virtual ~NavalVessel();

    const std::string& getName() const;
    const std::string& getType() const;
    int getHullIntegrity() const;
    int getArmorRating() const;
    double getSpeed() const;
    VesselState getState() const;
    std::string getStateName() const;
    const GridCoordinate& getPosition() const;
    bool isNeutralized() const;
    void takeDamage(int damage);
    void detectTarget();
    void engage();
    void neutralize();
    void updateStateBasedOnDetection(bool enemyDetected);
    virtual void calculateDamage(int incomingImpact, const std::string& weaponType) = 0;
    virtual void processTurnAction(NavalVessel* enemyTarget) = 0;
    virtual int getAttackPower() const = 0;
    virtual std::string getWeaponType() const = 0;
};

#endif // NAVALVESSEL_H
