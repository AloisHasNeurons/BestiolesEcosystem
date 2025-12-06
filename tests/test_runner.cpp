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
        {"Ears: Capability Zero", run_test_ears_capability_zero}
    };

    while (true) {
        std::cout << "\n=== Test Runner Menu ===\n";
        for (size_t i = 0; i < tests.size(); ++i) {
            if (i == 0) std::cout << "\n--- Eyes ---\n";
            if (i == 3) std::cout << "\n--- Ears ---\n";
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
