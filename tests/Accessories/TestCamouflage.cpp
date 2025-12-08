#include <iostream>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_camouflage() {
  std::cout << "Running Test Scenario: Camouflage Effectiveness" << std::endl;
  std::cout << "Observation: The Gregarious Creatures should NOT flock "
               "(Gregarious behavior absent) because they cannot see each "
               "other through the camouflage accessory."
            << std::endl;
  std::cout << "Close the simulation window to complete the test." << std::endl;

  // 1. Configure Eyes and Camouflage (Really good vision)
  SensorConfig cfg = Aquarium::getEyeConfig();
  cfg.alphaMin = 360.0;
  cfg.alphaMax = 360.0;
  cfg.deltaMin = 40.0;
  cfg.deltaMax = 45.0;
  cfg.gammaMin = 1.0;
  cfg.gammaMax = 1.0;
  Aquarium::setEyeConfig(cfg);

  AccessoryConfig accCfg = Aquarium::getAccessoryConfig();
  accCfg.camouflageMin = 1.0; // Very effective camouflage
  accCfg.camouflageMax = 1.0;
  Aquarium::setAccessoryConfig(accCfg);

  // 2. Initialize and Configure Elements of the simulation
  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();
  env.resetPopulation();

  // 3. Configure distribution of sensors and accessories
  env.setEyesAccessoryDistribution(
      {{"NoEyes", 0.0}, {"WithEyes", 1.0}}); // All have eyes
  env.setEarsAccessoryDistribution(
      {{"NoEars", 1.0}, {"WithEars", 0.0}}); // No need for ears
  env.setCamouflageAccessoryDistribution(
      {{"NoCamouflage", 0.0}, {"WithCamouflage", 1.0}}); // All have camouflage
  env.setFinsAccessoryDistribution(
      {{"NoFins", 1.0}, {"WithFins", 0.0}}); // No need for fins
  env.setShellAccessoryDistribution(
      {{"NoShell", 1.0}, {"WithShell", 0.0}}); // No need for shells

  // 4. Configure behavior distribution
  // All Gregarious
  env.setBehaviorDistribution({{"Anticipating", 0.0},
                               {"Fearfull", 0.0},
                               {"Gregarious", 1.0}, // All are Gregarious
                               {"Kamikaze", 0.0},
                               {"MultiPersonality", 0.0}});

  // 5. Run the simulation
  ecosystem.run();
}