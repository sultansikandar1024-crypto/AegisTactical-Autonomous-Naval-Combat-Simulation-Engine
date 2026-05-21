#include "WeatherSystem.h"
#include <cstdlib>

WeatherSystem::WeatherSystem()
    : currentCondition("Clear"), accuracyModifier(1.0), visibilityRange(10), weatherSeverity(0) {
}

void WeatherSystem::randomizeWeather() {
    int roll = std::rand() % 100;
    if (roll < 20) {
        setWeatherCondition("Heavy Fog");
    } else if (roll < 45) {
        setWeatherCondition("Stormy");
    } else {
        setWeatherCondition("Clear");
    }
}

void WeatherSystem::setWeatherCondition(const std::string& condition) {
    currentCondition = condition;
    if (condition == "Stormy") {
        accuracyModifier = 0.7;
        visibilityRange = 6;
        weatherSeverity = 2;
    } else if (condition == "Heavy Fog") {
        accuracyModifier = 0.5;
        visibilityRange = 4;
        weatherSeverity = 3;
    } else {
        accuracyModifier = 1.0;
        visibilityRange = 10;
        weatherSeverity = 1;
    }
}

std::string WeatherSystem::getCurrentCondition() const {
    return currentCondition;
}

double WeatherSystem::getAccuracyModifier() const {
    return accuracyModifier;
}

int WeatherSystem::getVisibilityRange() const {
    return visibilityRange;
}

std::string WeatherSystem::generateSummary() const {
    return "Weather: " + currentCondition + " | Accuracy modifier: " + std::to_string(accuracyModifier) + " | Visibility: " + std::to_string(visibilityRange);
}

bool WeatherSystem::isAdverse() const {
    return currentCondition == "Stormy" || currentCondition == "Heavy Fog";
}
