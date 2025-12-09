#include <iostream>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_cloning_spontaneous() {
  std::cout << "Running Test Scenario: Cloning Spontaneous" << std::endl;
  std::cout << "Observation: Exponential population growth (High cloning rate) and then death at the same time."
            << std::endl;

  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();

  // Force high clone rate
  Bestiole::setStartCloneRate(0.03);

  env.resetPopulation();
  env.setBirthRateProbability(0.0); // No spontaneous birth

  env.spawnPopulation(1);

  ecosystem.run();

  Bestiole::setStartCloneRate(-1.0);
}
