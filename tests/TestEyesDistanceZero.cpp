#include <iostream>
#include <map>
#include <string>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"

void run_test_eyes_distance_zero() {
    std::cout << "Running Test Scenario: Eyes (No Ears) - Distance Zero" << std::endl;
    std::cout << "Observation: Creatures should NOT flock (Gregarious behavior absent) because they cannot see anything (Distance=0)." << std::endl;
    std::cout << "Close the simulation window to complete the test." << std::endl;

    // 1. Configure Eyes (Zero Distance)
    SensorConfig cfg = Aquarium::getEyeConfig();
    cfg.alphaMin = M_PI; // Normal FOV
    cfg.alphaMax = M_PI;
    cfg.deltaMin = 0.0;  // Zero Distance
    cfg.deltaMax = 0.0;
    cfg.gammaMin = 0.5;
    cfg.gammaMax = 0.5;
    Aquarium::setEyeConfig(cfg);

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

    std::map<std::string, double> eyesDist = {{"WithEyes", 1.0}, {"NoEyes", 0.0}};
    env.setEyesAccessoryDistribution(eyesDist);

    std::map<std::string, double> earsDist = {{"WithEars", 0.0}, {"NoEars", 1.0}};
    env.setEarsAccessoryDistribution(earsDist);
    
    // Disable others
    env.setCamouflageAccessoryDistribution({{"WithCamouflage", 0.0}, {"NoCamouflage", 1.0}});
    env.setFinsAccessoryDistribution({{"WithFins", 0.0}, {"NoFins", 1.0}});
    env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

    // 4. Respawn population
    env.spawnPopulation(30);

    // 5. Run GUI
    ecosystem.run();
}
