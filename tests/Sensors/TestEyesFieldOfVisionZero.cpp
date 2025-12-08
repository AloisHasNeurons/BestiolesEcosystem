#include <iostream>
#include <map>
#include <string>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"

void run_test_eyes_field_of_vision_zero() {
  std::cout << "Running Test Scenario: Eyes (No Ears) - Field of Vision Zero"
            << std::endl;
  std::cout << "Observation: Creatures should NOT flock (Gregarious behavior "
               "absent) because they cannot see each other."
            << std::endl;
  std::cout << "Close the simulation window to complete the test." << std::endl;

  // 1. Configure Eyes (Zero FOV)
  SensorConfig cfg = Aquarium::getEyeConfig();
  cfg.alphaMin = 0.0;
  cfg.alphaMax = 0.0;
  cfg.deltaMin = 300.0;
  cfg.deltaMax = 300.0;
  cfg.gammaMin = 0.5;
  cfg.gammaMax = 0.5;
  Aquarium::setEyeConfig(cfg);

  // 2. Initialize Aquarium
  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();

  // 3. Configure Population
  // Clear initial random population
  env.resetPopulation();
  // Disable birth of random creatures during test
  env.setBirthRateProbability(0.0);

  // Only Gregarious creatures
  std::map<std::string, double> behaviorDist;
  behaviorDist["Gregarious"] = 1.0;
  behaviorDist["Anticipating"] = 0.0;
  behaviorDist["Fearfull"] = 0.0;
  behaviorDist["Kamikaze"] = 0.0;
  behaviorDist["MultiPersonality"] = 0.0;
  env.setBehaviorDistribution(behaviorDist);

  // Only Eyes, No Ears
  std::map<std::string, double> eyesDist = {{"WithEyes", 1.0}, {"NoEyes", 0.0}};
  env.setEyesAccessoryDistribution(eyesDist);

  std::map<std::string, double> earsDist = {{"WithEars", 0.0}, {"NoEars", 1.0}};
  env.setEarsAccessoryDistribution(earsDist);

  // Disable others to be clean
  env.setCamouflageAccessoryDistribution(
      {{"WithCamouflage", 0.0}, {"NoCamouflage", 1.0}});
  env.setFinsAccessoryDistribution({{"WithFins", 0.0}, {"NoFins", 1.0}});
  env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

  // 4. Respawn population
  env.spawnPopulation(30);

  // 5. Run GUI
  ecosystem.run();
}
