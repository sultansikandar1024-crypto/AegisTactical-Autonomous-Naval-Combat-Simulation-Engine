#include "BattleLog.h"
#include <iostream>

BattleLog::BattleLog()
    : eventCount(0), lastMessage("Simulation Start") {
    entries.push_back(lastMessage);
}

void BattleLog::logEvent(const std::string& message) {
    eventCount++;
    lastMessage = message;
    entries.push_back(message);
    std::cout << "[Event " << eventCount << "] " << message << std::endl;
}

void BattleLog::logStatusReport(const std::string& vesselName, const std::string& state, int hullIntegrity, const std::string& location) {
    std::string report = "Status - " + vesselName + " | State: " + state + " | Hull: " + std::to_string(hullIntegrity) + " | Location: " + location;
    logEvent(report);
}

void BattleLog::logWeatherUpdate(const std::string& weatherSummary) {
    logEvent(weatherSummary);
}

void BattleLog::printRecentEvents(int count) const {
    std::cout << "--- Recent Battle Events ---" << std::endl;
    int start = static_cast<int>(entries.size()) - count;
    if (start < 0) {
        start = 0;
    }
    for (int i = start; i < static_cast<int>(entries.size()); ++i) {
        std::cout << entries[i] << std::endl;
    }
}

void BattleLog::flushLog() const {
    std::cout << "--- Battle Log Flush ---" << std::endl;
    for (const auto& entry : entries) {
        std::cout << entry << std::endl;
    }
}

int BattleLog::getEventCount() const {
    return eventCount;
}
