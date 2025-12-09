#include "menu/SimulationMenu.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <numeric>
#include <string>
#include <vector>

// ANSI Color Codes
const char RESET[] = "\033[0m";
const char BOLD[] = "\033[1m";
const char RED[] = "\033[31m";
const char YELLOW[] = "\033[33m";
const char CYAN[] = "\033[36m";
const char GREEN[] = "\033[32m";
const char MAGENTA[] = "\033[35m";

SimulationMenu::SimulationMenu() {}

void SimulationMenu::clearScreen() {
  std::cout << "\033[2J\033[H";
}

int SimulationMenu::getIntInput(const std::string &prompt, int defaultValue) {
  std::string input;
  while (true) {
    if (!prompt.empty()) {
      std::cout << prompt;
    }
    std::getline(std::cin, input);

    if (input.empty()) {
      if (defaultValue != -1) return defaultValue;
      // If no default value, we iterate to get a value
      continue;
    }

    try {
      return std::stoi(input);
    } catch (const std::exception &) {
      std::cout << RED << "Invalid input. Please enter a number."
                << RESET << "\n";
    }
  }
}

double SimulationMenu::getDoubleInput(const std::string &prompt,
                                      double defaultValue) {
  std::string input;
  while (true) {
    if (!prompt.empty()) {
      std::cout << prompt;
    }
    std::getline(std::cin, input);

    if (input.empty()) {
      if (defaultValue != -1.0) return defaultValue;
      continue;
    }

    try {
      return std::stod(input);
    } catch (const std::exception &) {
      std::cout << RED << "Invalid input. Please enter a number."
                << RESET << "\n";
    }
  }
}

bool SimulationMenu::validateProbabilities(
    const std::map<std::string, double> &dist) {
  double sum = 0.0;
  for (const auto &pair : dist) {
    sum += pair.second;
  }
  // Check if sum is close to 1.0 (allow slight precision error)
  if (std::abs(sum - 1.0) > 0.01) {
    std::cout << RED << "WARNING: probabilities sum to " << sum
              << " (should be 1.0)" << RESET << "\n";
    return false;
  }
  return true;
}

void SimulationMenu::configurePhysics(SimulationConfig &config) {
  while (true) {
    clearScreen();
    std::cout << BOLD << CYAN << "=== Physics Configuration ==="
              << RESET << "\n";
    std::cout << "1. Screen Width: " << config.width << "\n";
    std::cout << "2. Screen Height: " << config.height << "\n";
    std::cout << "3. Delay (ms): " << config.delay << "\n";
    std::cout << "4. Max Speed: " << config.maxSpeed << "\n";
    std::cout << "5. Min Speed: " << config.minSpeed << "\n";
    std::cout << "0. " << CYAN << "Back to Main Menu (Default)" << RESET
              << "\n";
    std::cout << "> ";

    int choice = getIntInput("", 0);

    switch (choice) {
      case 0: return;
      case 1: config.width = getIntInput("Enter new width: "); break;
      case 2: config.height = getIntInput("Enter new height: "); break;
      case 3: config.delay = getIntInput("Enter new delay (ms): "); break;
      case 4: config.maxSpeed = getDoubleInput("Enter Max Speed: "); break;
      case 5: config.minSpeed = getDoubleInput("Enter Min Speed: "); break;
      default: std::cout << RED << "Invalid selection." << RESET << "\n";
    }
  }
}

void SimulationMenu::configurePopulation(SimulationConfig &config) {
  while (true) {
    clearScreen();
    std::cout << BOLD << GREEN << "=== Initial Population Configuration ==="
              << RESET << "\n";
    int i = 1;
    std::vector<std::string> keys;
    for (const auto &pair : config.initialPopulation) {
      std::cout << i++ << ". " << pair.first << ": " << pair.second << "\n";
      keys.push_back(pair.first);
    }
    std::cout << "0. " << CYAN << "Back to Main Menu (Default)" << RESET
              << "\n";
    std::cout << "> ";

    int choice = getIntInput("", 0);

    if (choice == 0) return;

    if (choice > 0 && choice <= static_cast<int>(keys.size())) {
      std::string key = keys[choice - 1];
      config.initialPopulation[key] =
          getIntInput("Enter new count for " + key + ": ");
    } else {
      std::cout << RED << "Invalid selection." << RESET << "\n";
    }
  }
}

void SimulationMenu::configureProbabilities(SimulationConfig &config) {
  while (true) {
    clearScreen();
    std::cout << BOLD << MAGENTA
              << "=== Spontaneous Birth Probabilities (Must sum to 1.0) ==="
              << RESET << "\n";
    int i = 1;
    std::vector<std::string> keys;
    double sum = 0;
    for (const auto &pair : config.spawnProbabilities) {
      std::cout << i++ << ". " << pair.first << ": " << pair.second << "\n";
      keys.push_back(pair.first);
      sum += pair.second;
    }
    std::cout << BOLD << "Total Probability: " << sum << RESET << "\n";
    validateProbabilities(config.spawnProbabilities);

    std::cout << "0. " << CYAN << "Back to Main Menu (Default)" << RESET
              << "\n";
    std::cout << "> ";

    int choice = getIntInput("", 0);

    if (choice == 0) return;

    if (choice > 0 && choice <= static_cast<int>(keys.size())) {
      std::string key = keys[choice - 1];
      config.spawnProbabilities[key] =
          getDoubleInput("Enter new probability for " + key + ": ");
    } else {
      std::cout << RED << "Invalid selection." << RESET << "\n";
    }
  }
}

void SimulationMenu::configureAccessories(SimulationConfig &config) {
  while (true) {
    clearScreen();
    std::cout << BOLD << YELLOW
              << "=== Accessory & Sensor Presence Probabilities (0.0 - 1.0) ==="
              << RESET << "\n";
    int i = 1;
    std::vector<std::string> keys;
    for (const auto &pair : config.accessories) {
      std::cout << i++ << ". " << pair.first << ": " << pair.second << "\n";
      keys.push_back(pair.first);
    }
    std::cout << "0. " << CYAN << "Back to Main Menu (Default)" << RESET
              << "\n";
    std::cout << "> ";

    int choice = getIntInput("", 0);

    if (choice == 0) return;

    if (choice > 0 && choice <= static_cast<int>(keys.size())) {
      std::string key = keys[choice - 1];
      config.accessories[key] =
          getDoubleInput("Enter new probability for " + key + ": ");
    } else {
      std::cout << RED << "Invalid selection." << RESET << "\n";
    }
  }
}

void SimulationMenu::run(SimulationConfig &config) {
  while (true) {
    clearScreen();
    std::cout << BOLD << "=== Bestioles Ecosystem Main Menu ==="
              << RESET << "\n";
    std::cout << "1. Configure Initial Population\n";
    std::cout << "2. Configure Birth Probabilities\n";
    std::cout << "3. Configure Accessories & Sensors\n";
    std::cout << "4. Configure Physics & World\n";
    std::cout << "5. " << GREEN << "LAUNCH SIMULATION (Default)" << RESET
              << "\n";
    std::cout << "0. Exit\n";
    std::cout << "> ";

    int choice = getIntInput("", 5);  // Default is Launch (5)

    if (choice == 0) exit(0);
    if (choice == 5) break;

    switch (choice) {
      case 1: configurePopulation(config); break;
      case 2: configureProbabilities(config); break;
      case 3: configureAccessories(config); break;
      case 4: configurePhysics(config); break;
      default: std::cout << RED << "Invalid selection." << RESET << "\n";
    }
  }
}
