#ifndef STATS_COLLECTOR_H
#define STATS_COLLECTOR_H

#include <map>
#include <string>
#include <vector>

#include "interfaces/IBestiole.h"

struct BestioleStats {
  std::string behavior;
  int count;
  // Future: Add accessories and sensors counts here
};

class StatsCollector {
 public:
  StatsCollector();
  ~StatsCollector();

  void track(const std::vector<IBestiole*>& bestioles, int stepCount);
  void addEvent(const std::string& event);
  void printSummary(int stepCount);
  void writeToCSV(int stepCount);

 private:
  std::map<std::string, int> m_behaviorCounts;
  std::vector<std::string> m_events;
  // Helper to clear terminal
  void clearTerminal();
};

#endif  // STATS_COLLECTOR_H
