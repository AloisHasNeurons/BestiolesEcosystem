#include "TestUtils.h"
#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "core/Bestiole.h"
#include "core/Environment.h"
#include "patterns/Factory.h"

// ANSI Color Codes
const char RESET[] = "\033[0m";
const char BOLD[] = "\033[1m";
const char CYAN[] = "\033[36m";
const char GREEN[] = "\033[32m";
const char RED[] = "\033[31m";

struct TestScenario {
  std::string name;
  std::function<void()> run;
};

void clearScreen() { std::cout << "\033[2J\033[H"; }

int main() {
  std::vector<TestScenario> tests = {
      {"Eyes: Field of Vision Zero", run_test_eyes_field_of_vision_zero},
      {"Eyes: Distance Zero", run_test_eyes_distance_zero},
      {"Eyes: Detection Range Zero", run_test_eyes_detection_range_zero},
      {"Ears: Distance Zero", run_test_ears_distance_zero},
      {"Ears: Capability Zero", run_test_ears_capability_zero},

      // Birth
      {"Birth: Spontaneous", run_test_birth_spontaneous},
      {"Birth: Rate Validation", run_test_birth_rate_validation},
      {"Birth: Zero Cloning", run_test_birth_with_zero_cloning},

      // Cloning
      {"Cloning: Spontaneous", run_test_cloning_spontaneous},

      // Collision
      {"Collision: Bounce (No Death)", run_test_collision_bounce_no_death},
      {"Collision: Death", run_test_death_by_collision},

      // Death
      {"Natural Death (Max Resistance)",
       run_test_natural_death_only_with_max_resistance},

      // Accessory Tests
      {"Camouflage Effectiveness", run_test_camouflage},
      {"Fin Effectiveness", run_test_fin},
      {"Shell Effectiveness", run_test_shell},

      // Behaviors Tests
      {"Gregarious Behavior Test", run_test_gregarious_behavior},
      {"Fearful Behavior Test", run_test_fearful_behavior},
      {"Kamikaze Behavior Test", run_test_kamikaze_behavior},
      {"Anticipating Behavior Test", run_test_anticipating_behavior},
      {"MultiPersonality Behavior Test", run_test_multipersonality_behavior}

  };

  while (true) {
    clearScreen();
    std::cout << BOLD << CYAN << "=== Test Runner Menu ===\n" << RESET;

    int columns = 0;

    for (size_t i = 0; i < tests.size(); ++i) {
      if (i == 0) {
        std::cout << BOLD << GREEN << "\n--- Eyes ---\n" << RESET;
        columns = 0;
      }
      if (i == 3) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Ears ---\n" << RESET;
        columns = 0;
      }
      if (i == 5) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Birth ---\n" << RESET;
        columns = 0;
      }
      if (i == 8) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Cloning ---\n" << RESET;
        columns = 0;
      }
      if (i == 9) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Collision ---\n" << RESET;
        columns = 0;
      }
      if (i == 11) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Death ---\n" << RESET;
        columns = 0;
      }
      if (i == 12) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Accessories ---\n" << RESET;
        columns = 0;
      }
      if (i == 15) {
        if (columns % 2 != 0) std::cout << "\n";
        std::cout << BOLD << GREEN << "\n--- Behaviors ---\n" << RESET;
        columns = 0;
      }

      std::string item = std::to_string(i + 1) + ". " + tests[i].name;
      if (columns % 2 == 0) {
          std::cout << std::left << std::setw(50) << item;
      } else {
          std::cout << item << "\n";
      }
      columns++;
    }
    // Check if the last line needs a newline
    if (columns % 2 != 0) std::cout << "\n";

    std::cout << "\n0. " << RED << "Exit (Default)" << RESET << "\n";
    std::cout << BOLD << "Select a test to run: " << RESET;

    std::string input;
    std::getline(std::cin, input);

    int choice = 0; // Default to Exit
    if (!input.empty()) {
      try {
        choice = std::stoi(input);
      } catch (const std::exception&) {
        std::cout << RED << "Invalid input. Please enter a number.\n" << RESET;
        std::cout << "Press Enter to continue...";
        std::getline(std::cin, input);
        continue;
      }
    }

    if (choice == 0) {
      std::cout << "Exiting...\n";
      break;
    }

    if (choice > 0 && static_cast<size_t>(choice) <= tests.size()) {
      clearScreen();
      std::cout << BOLD << CYAN << "\n--- Running "
                << tests[choice - 1].name << " ---\n" << RESET;
      tests[choice - 1].run();

      // === CLEANUP GLOBAL STATE ===
      
      // Also reset Bestiole statics (which are public static methods)
      Bestiole::setStartCloneRate(-1.0);
      Bestiole::setStartResistance(-1.0);
      // Bestiole::setStartCloneRate is static void setStartCloneRate(double r) { startCloneRate = r; }
      
      Factory cleanupFactory;
      Environment cleanupEnv(cleanupFactory);
      cleanupEnv.setBirthRateProbability(0.1); 
      
      std::cout << "\n" << BOLD << "Press Enter to return to menu..." << RESET;
      std::string dummy;
      std::getline(std::cin, dummy);
    } else {
      std::cout << RED << "Invalid selection.\n" << RESET;
      std::cout << "Press Enter to continue...";
      std::string dummy;
      std::getline(std::cin, dummy);
    }
  }

  return 0;
}
