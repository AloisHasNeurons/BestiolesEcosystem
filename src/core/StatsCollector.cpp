#include "core/StatsCollector.h"

#include <sys/stat.h>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

StatsCollector::StatsCollector() {
  // Create outputs directory if it doesn't exist
  struct stat st = {0};
  if (stat("outputs", &st) == -1) {
#ifdef _WIN32
    mkdir("outputs");
#else
    mkdir("outputs", 0700);
#endif
  }

  // Initialize CSV with header
  std::ofstream csvFile("outputs/simulation_log.csv");
  if (csvFile.is_open()) {
    csvFile << "Step,Behavior,Accessories,Sensors,Count,Events\n";
    csvFile.close();
  }
}

StatsCollector::~StatsCollector() {}

void StatsCollector::addEvent(const std::string& event) {
  m_events.push_back(event);
}

#include <algorithm> // for sort
#include <numeric>   // for accumulate

// Helper to join strings
std::string join(const std::vector<std::string>& v,
                 const std::string& delimiter) {
  if (v.empty()) return "None";
  return std::accumulate(std::next(v.begin()), v.end(), v[0],
                         [&delimiter](std::string a, std::string b) {
                           return a + delimiter + b;
                         });
}

void StatsCollector::track(const std::vector<IBestiole*>& bestioles,
                           int stepCount) {
  m_statsCounts.clear();

  for (const auto& bestiole : bestioles) {
    std::string behavior = bestiole->getBehaviorString();

    std::vector<std::string> accessories = bestiole->getAccessories();
    std::sort(accessories.begin(), accessories.end());
    std::string accStr = join(accessories, ", ");

    std::vector<std::string> sensors = bestiole->getSensors();
    std::sort(sensors.begin(), sensors.end());
    std::string sensStr = join(sensors, ", ");

    m_statsCounts[std::make_tuple(behavior, accStr, sensStr)]++;
  }

  printSummary(stepCount);
  writeToCSV(stepCount);
}

void StatsCollector::printSummary(int stepCount) {
  // ANSI Color Codes
  const std::string RESET = "\033[0m";
  const std::string BOLD = "\033[1m";
  const std::string RED = "\033[31m";      // Kamikaze
  const std::string GREEN = "\033[32m";    // Fearful
  const std::string YELLOW = "\033[33m";   // Gregarious
  const std::string BLUE = "\033[34m";     // Anticipating
  const std::string MAGENTA = "\033[35m";  // MultiPersonality
  const std::string CYAN = "\033[36m";     // Default/Other

  std::cout << "\n" << BOLD << "--- Simulation Step: " << stepCount
            << " ---" << RESET << "\n";
  std::cout << std::left << std::setw(20) << "Behavior"
            << "| " << std::setw(30) << "Accessories"
            << "| " << std::setw(20) << "Sensors"
            << "| " << std::setw(10) << "Count" << "\n";
  std::cout << std::string(85, '-') << "\n";

  for (const auto& pair : m_statsCounts) {
    std::string behavior = std::get<0>(pair.first);
    std::string accessories = std::get<1>(pair.first);
    std::string sensors = std::get<2>(pair.first);
    int count = pair.second;

    std::string color = RESET;
    if (behavior == "Kamikaze") color = RED;
    else if (behavior == "Fearful") color = BLUE;
    else if (behavior == "Gregarious") color = GREEN;
    else if (behavior == "Anticipating") color = MAGENTA;
    else if (behavior == "MultiPersonality") color = CYAN;
    else color = YELLOW;

    if (behavior == "MultiPersonality") {
      std::cout << MAGENTA << "Mult" << GREEN << "iPer" << BLUE << "sona" << RED
                << "lity" << RESET << std::left << std::setw(4) << "" << RESET
                << "| " << std::setw(30) << accessories
                << "| " << std::setw(20) << sensors
                << "| " << std::setw(10) << count << "\n";
    } else {
      std::cout << color << std::left << std::setw(20) << behavior << RESET
                << "| " << std::setw(30) << accessories
                << "| " << std::setw(20) << sensors
                << "| " << std::setw(10) << count << "\n";
    }
  }
  std::cout << std::string(85, '-') << "\n";

  if (!m_events.empty()) {
    std::cout << BOLD << "Events:" << RESET << "\n";
    for (const auto& event : m_events) {
      std::string formattedEvent = event;
      // Bold keywords
      std::vector<std::string> keywords = {"Birth of", "Natural death of",
                                           "killed", "Clone of"};
      for (const auto& kw : keywords) {
        size_t pos = 0;
        while ((pos = formattedEvent.find(kw, pos)) != std::string::npos) {
          formattedEvent.replace(pos, kw.length(), BOLD + kw + RESET);
          pos += BOLD.length() + kw.length() + RESET.length();
        }
      }

      // Color behaviors
      std::map<std::string, std::string> behaviorColors = {
          {"Kamikaze", RED},
          {"Fearful", BLUE},
          {"Gregarious", GREEN},
          {"Anticipating", MAGENTA}};

      for (const auto& b : behaviorColors) {
        size_t pos = 0;
        while ((pos = formattedEvent.find(b.first, pos)) != std::string::npos) {
          formattedEvent.replace(pos, b.first.length(),
                                 b.second + b.first + RESET);
          pos += b.second.length() + b.first.length() + RESET.length();
        }
      }

      // Rainbow MultiPersonality in events
      std::string mp = "MultiPersonality";
      size_t pos = 0;
      while ((pos = formattedEvent.find(mp, pos)) != std::string::npos) {
        std::string rainbowMP = MAGENTA + std::string("Mult") + GREEN + "iPer" +
                                BLUE + "sona" + RED + "lity" + RESET;
        formattedEvent.replace(pos, mp.length(), rainbowMP);
        pos += rainbowMP.length();
      }

      std::cout << " - " << formattedEvent << "\n";
    }
    std::cout << std::string(85, '-') << "\n";
  }
}

void StatsCollector::writeToCSV(int stepCount) {
  std::ofstream csvFile("outputs/simulation_log.csv", std::ios::app);
  if (csvFile.is_open()) {
    std::string eventsStr = "";
    if (!m_events.empty()) {
      eventsStr = "[";
      for (size_t i = 0; i < m_events.size(); ++i) {
        eventsStr += m_events[i];
        if (i < m_events.size() - 1) eventsStr += "; ";
      }
      eventsStr += "]";
    }

    for (const auto& pair : m_statsCounts) {
      csvFile << stepCount << ","
              << std::get<0>(pair.first) << ","
              << std::get<1>(pair.first) << ","
              << std::get<2>(pair.first) << ","
              << pair.second << ","
              << eventsStr << "\n";
    }
    csvFile.close();
  }
  m_events.clear();
}

void StatsCollector::clearTerminal() {
    // Optional: Clear screen command if needed, but scrolling might be better
    // for history
    // std::cout << "\033[2J\033[1;1H";
}
