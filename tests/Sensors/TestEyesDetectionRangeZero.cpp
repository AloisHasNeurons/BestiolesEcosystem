#include <iostream>
#include <map>
#include <string>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"

void run_test_eyes_detection_range_zero() {
  std::cout
      << "Running Test Scenario: Eyes (No Ears) - Detection Capability Zero"
      << std::endl;
  std::cout << "Observation: Creatures should NOT flock because their "
               "detection capability (Gamma) is 0."
            << std::endl;
  std::cout << "Close the simulation window to complete the test." << std::endl;

  // 1. Configure Eyes (Zero Gamma)
  SensorConfig cfg = Aquarium::getEyeConfig();
  cfg.alphaMin = M_PI;
  cfg.alphaMax = M_PI;
  cfg.deltaMin = 300.0;
  cfg.deltaMax = 300.0;
  cfg.gammaMin = 0.0; // Zero Capability
  cfg.gammaMax = 0.0;
  Aquarium::setEyeConfig(cfg);

  // 2. Initialize Aquarium
  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();

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

  // Only Eyes, No Ears
  env.setEyesAccessoryDistribution({{"WithEyes", 1.0}, {"NoEyes", 0.0}});
  env.setEarsAccessoryDistribution({{"WithEars", 0.0}, {"NoEars", 1.0}});

  // Disable others
  env.setCamouflageAccessoryDistribution(
      {{"WithCamouflage", 0.0}, {"NoCamouflage", 1.0}});
  env.setFinsAccessoryDistribution({{"WithFins", 0.0}, {"NoFins", 1.0}});
  env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

  // 4. Respawn population
  env.spawnPopulation(30);

  // 5. Run GUI
  ecosystem.run();
}
