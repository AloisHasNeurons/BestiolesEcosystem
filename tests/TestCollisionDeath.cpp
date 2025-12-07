#include <iostream>
#include <map>
#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"
#include "core/Bestiole.h"

void run_test_death_by_collision() {
    std::cout << "Running Test Scenario: Death by Collision" << std::endl;
    std::cout << "Observation: Kamikaze & Gregarious. Collisions = Death. Births enabled." << std::endl;

    Aquarium ecosystem(800, 600, 30);
    Environment& env = ecosystem.getEnvironment();
    Bestiole::setStartCloneRate(0.0);
    Bestiole::setStartResistance(0.0); // Vulnerable

    env.resetPopulation();
    // Enable birth
    env.setBirthRateProbability(0.05);

    std::map<std::string, double> dist;
    dist["Kamikaze"] = 0.5;
    dist["Gregarious"] = 0.5;
    dist["Fearfull"] = 0.0;
    dist["Anticipating"] = 0.0;
    dist["MultiPersonality"] = 0.0;
    env.setBehaviorDistribution(dist);

    // Allow accessories? User said "Collision... death upon impact". 
    // To be safe and ensure high death rate, maybe disable Shell.
    env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

    env.spawnPopulation(30);
    
    // Using static resistance
    
    ecosystem.run();
    Bestiole::setStartCloneRate(-1.0);
    Bestiole::setStartResistance(-1.0);
}
