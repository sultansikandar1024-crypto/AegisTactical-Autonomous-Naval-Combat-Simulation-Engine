#ifndef WEATHERSYSTEM_H
#define WEATHERSYSTEM_H

#include <string>

class WeatherSystem {
private:
    std::string currentCondition;
    double accuracyModifier;
    int visibilityRange;
    int weatherSeverity;

public:
    WeatherSystem();
    void randomizeWeather();
    void setWeatherCondition(const std::string& condition);
    std::string getCurrentCondition() const;
    double getAccuracyModifier() const;
    int getVisibilityRange() const;
    std::string generateSummary() const;
    bool isAdverse() const;
};

#endif // WEATHERSYSTEM_H
