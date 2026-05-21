#include "NavalVessel.h"

NavalVessel::NavalVessel(const std::string& name, const std::string& type, int hull, int armor, double speed, const GridCoordinate& location)
    : vesselName(name), vesselType(type), hullIntegrity(hull), armorRating(armor), speed(speed), detected(false), currentState(VesselState::Stealth), position(location) {
}

NavalVessel::~NavalVessel() {
}

const std::string& NavalVessel::getName() const {
    return vesselName;
}

const std::string& NavalVessel::getType() const {
    return vesselType;
}

int NavalVessel::getHullIntegrity() const {
    return hullIntegrity;
}

int NavalVessel::getArmorRating() const {
    return armorRating;
}

double NavalVessel::getSpeed() const {
    return speed;
}

VesselState NavalVessel::getState() const {
    return currentState;
}

std::string NavalVessel::getStateName() const {
    switch (currentState) {
        case VesselState::Stealth: return "Stealth";
        case VesselState::Spotted: return "Spotted";
        case VesselState::Engaged: return "Engaged";
        case VesselState::Neutralized: return "Neutralized";
    }
    return "Unknown";
}

const GridCoordinate& NavalVessel::getPosition() const {
    return position;
}

bool NavalVessel::isNeutralized() const {
    return currentState == VesselState::Neutralized || hullIntegrity <= 0;
}

void NavalVessel::takeDamage(int damage) {
    int effectiveDamage = damage - armorRating;
    if (effectiveDamage < 0) {
        effectiveDamage = 0;
    }
    hullIntegrity -= effectiveDamage;
    if (hullIntegrity <= 0) {
        hullIntegrity = 0;
        neutralize();
    } else if (currentState == VesselState::Stealth) {
        currentState = VesselState::Spotted;
    } else {
        currentState = VesselState::Engaged;
    }
}

void NavalVessel::detectTarget() {
    detected = true;
    if (currentState == VesselState::Stealth) {
        currentState = VesselState::Spotted;
    }
}

void NavalVessel::engage() {
    if (currentState != VesselState::Neutralized) {
        currentState = VesselState::Engaged;
    }
}

void NavalVessel::neutralize() {
    currentState = VesselState::Neutralized;
}

void NavalVessel::updateStateBasedOnDetection(bool enemyDetected) {
    if (enemyDetected && currentState == VesselState::Stealth) {
        currentState = VesselState::Spotted;
    }
}
