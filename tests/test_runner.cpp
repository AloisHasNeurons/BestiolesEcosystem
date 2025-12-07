#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <limits>
#include "TestUtils.h"

struct TestScenario {
    std::string name;
    std::function<void()> run;
};

int main() {
    std::vector<TestScenario> tests = {
        {"Eyes: Field of Vision Zero", run_test_eyes_field_of_vision_zero},
        {"Eyes: Distance Zero", run_test_eyes_distance_zero},
        {"Eyes: Detection Range Zero", run_test_eyes_detection_range_zero},
        {"Ears: Distance Zero", run_test_ears_distance_zero},
        {"Ears: Capability Zero", run_test_ears_capability_zero},
        
        // Issue #22 Tests - Birth
        {"Birth: Spontaneous", run_test_birth_spontaneous},
        {"Birth: Rate Validation", run_test_birth_rate_validation},
        {"Birth: Zero Cloning", run_test_birth_with_zero_cloning},
        
        // Issue #22 Tests - Cloning
        {"Cloning: Spontaneous", run_test_cloning_spontaneous},
        
        // Issue #22 Tests - Collision
        {"Collision: Bounce (No Death)", run_test_collision_bounce_no_death},
        {"Collision: Death", run_test_death_by_collision},
        
        // Issue #22 Tests - Death
        {"Natural Death (Max Resistance)", run_test_natural_death_only_with_max_resistance},

        // Accessory Tests
        {"Camouflage Effectiveness", run_test_camouflage},
        {"Fin Effectiveness", run_test_fin},
        {"Shell Effectiveness", run_test_shell}
    };

    while (true) {
        std::cout << "\n=== Test Runner Menu ===\n";
        for (size_t i = 0; i < tests.size(); ++i) {
            if (i == 0) std::cout << "\n--- Eyes ---\n";
            if (i == 3) std::cout << "\n--- Ears ---\n";
            if (i == 5) std::cout << "\n--- Birth ---\n";
            if (i == 8) std::cout << "\n--- Cloning ---\n";
            if (i == 9) std::cout << "\n--- Collision ---\n";
            if (i == 11) std::cout << "\n--- Death ---\n";
            if (i == 12) std::cout << "\n--- Accessories ---\n";
            std::cout << i + 1 << ". " << tests[i].name << "\n";
        }
        std::cout << "0. Exit\n";
        std::cout << "Select a test to run: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 0) {
            std::cout << "Exiting...\n";
            break;
        }

        if (choice > 0 && static_cast<size_t>(choice) <= tests.size()) {
            std::cout << "\n--- Running " << tests[choice - 1].name << " ---\n";
            tests[choice - 1].run();
        } else {
            std::cout << "Invalid selection.\n";
        }
    }

    return 0;
}
