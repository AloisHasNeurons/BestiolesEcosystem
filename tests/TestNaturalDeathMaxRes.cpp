#include <iostream>
#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"
#include "core/Bestiole.h"

void run_test_natural_death_only_with_max_resistance() {
    std::cout << "Running Test Scenario: Natural Death (Max Resistance)" << std::endl;
    std::cout << "Observation: Creatures disappear only due to aging. No collision deaths." << std::endl;

    Aquarium ecosystem(800, 600, 30);
    Environment& env = ecosystem.getEnvironment();
    Bestiole::setStartCloneRate(0.0);
    Bestiole::setStartResistance(1.0); // Max resistance

    env.resetPopulation();
    env.setBirthRateProbability(0.0);

    // Disable accessories to avoid Armor modification
    env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

    env.spawnPopulation(20);
    
    ecosystem.run();
    Bestiole::setStartCloneRate(-1.0);
    Bestiole::setStartResistance(-1.0);
}
