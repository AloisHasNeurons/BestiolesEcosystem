#include <iostream>
#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"
#include "core/Bestiole.h"

void run_test_birth_spontaneous() {
    std::cout << "Running Test Scenario: Birth Spontaneous" << std::endl;
    std::cout << "Observation: New creatures should appear spontaneously." << std::endl;

    Aquarium ecosystem(800, 600, 30);
    Environment& env = ecosystem.getEnvironment();
    
    // Ensure default behavior
    Bestiole::setStartCloneRate(-1.0); 

    env.resetPopulation();
    env.setBirthRateProbability(0.5); 

    ecosystem.run();
}
