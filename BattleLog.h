#ifndef BATTLELOG_H
#define BATTLELOG_H

#include <string>
#include <vector>

class BattleLog {
private:
    int eventCount;
    std::string lastMessage;
    std::vector<std::string> entries;

public:
    BattleLog();
    void logEvent(const std::string& message);
    void logStatusReport(const std::string& vesselName, const std::string& state, int hullIntegrity, const std::string& location);
    void logWeatherUpdate(const std::string& weatherSummary);
    void printRecentEvents(int count = 5) const;
    void flushLog() const;
    int getEventCount() const;
};

#endif // BATTLELOG_H
