#include <iostream>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_birth_rate_validation() {
  std::cout << "Running Test Scenario: Birth Rate Validation" << std::endl;
  std::cout << "Observation: Verify that roughly 10 creatures are born in 100 "
               "steps with 0.1 rate."
            << std::endl;

  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();
  Bestiole::setStartCloneRate(-1.0);

  env.resetPopulation();
  env.setBirthRateProbability(0.1);

  ecosystem.run();
}
