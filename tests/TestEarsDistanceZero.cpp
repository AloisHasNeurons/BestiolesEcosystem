#include <iostream>
#include <map>
#include <string>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"

void run_test_ears_distance_zero() {
    std::cout << "Running Test Scenario: Ears (No Eyes) - Distance Zero" << std::endl;
    std::cout << "Observation: Creatures should NOT flock because their hearing distance is 0." << std::endl;
    std::cout << "Close the simulation window to complete the test." << std::endl;

    // 1. Configure Ears (Zero Distance)
    SensorConfig cfg = Aquarium::getEarConfig();
    cfg.deltaMin = 0.0;
    cfg.deltaMax = 0.0;
    cfg.gammaMin = 0.5;
    cfg.gammaMax = 0.5;
    Aquarium::setEarConfig(cfg);

    // 2. Initialize Aquarium
    Aquarium ecosystem(800, 600, 30);
    Environment& env = ecosystem.getEnvironment();

    // 3. Configure Population
    env.resetPopulation();
    env.setBirthRateProbability(0.0);

    std::map<std::string, double> behaviorDist;
    behaviorDist["Gregarious"] = 1.0;
    behaviorDist["Anticipating"] = 0.0;
    behaviorDist["Fearfull"] = 0.0;
    behaviorDist["Kamikaze"] = 0.0;
    behaviorDist["MultiPersonality"] = 0.0;
    env.setBehaviorDistribution(behaviorDist);

    // Only Ears, No Eyes
    env.setEyesAccessoryDistribution({{"WithEyes", 0.0}, {"NoEyes", 1.0}});
    env.setEarsAccessoryDistribution({{"WithEars", 1.0}, {"NoEars", 0.0}});
    
    // Disable others
    env.setCamouflageAccessoryDistribution({{"WithCamouflage", 0.0}, {"NoCamouflage", 1.0}});
    env.setFinsAccessoryDistribution({{"WithFins", 0.0}, {"NoFins", 1.0}});
    env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

    // 4. Respawn population
    env.spawnPopulation(30);

    // 5. Run GUI
    ecosystem.run();
}
