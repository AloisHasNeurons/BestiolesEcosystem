#include <iostream>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_birth_with_zero_cloning() {
  std::cout << "Running Test Scenario: Birth with Zero Cloning" << std::endl;
  std::cout << "Observation: New creatures should appear at RANDOM locations. "
               "No cloning (spawning near parent) should occur."
            << std::endl;

  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();

  // Force zero clone rate for all new bestioles
  Bestiole::setStartCloneRate(0.0);

  env.resetPopulation();
  env.setBirthRateProbability(0.5);

  ecosystem.run();

  // Restore default
  Bestiole::setStartCloneRate(-1.0);
}
