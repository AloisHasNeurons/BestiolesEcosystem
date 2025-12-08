#include <iostream>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_fin() {
  std::cout << "Running Test Scenario: Fin Effectiveness" << std::endl;
  std::cout << "Observation: Bestioles with fins should move significantly "
               "faster than those without fins."
            << std::endl;
  std::cout << "Close the simulation window to complete the test." << std::endl;

  // 1. Configure fins (High speed factor)
  AccessoryConfig finConfig;
  finConfig.nuMin = 10.0;
  finConfig.nuMax = 10.0;
  Aquarium::setAccessoryConfig(finConfig);

  // 2. Initialize and Configure Elements of the simulation
  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();
  env.resetPopulation();

  // 3. Configure distribution of sensors and accessories
  env.setEyesAccessoryDistribution(
      {{"NoEyes", 1.0}, {"WithEyes", 0.0}}); // No need for eyes
  env.setEarsAccessoryDistribution(
      {{"NoEars", 1.0}, {"WithEars", 0.0}}); // No need for ears
  env.setCamouflageAccessoryDistribution(
      {{"NoCamouflage", 1.0},
       {"WithCamouflage", 0.0}}); // No need for camouflage
  env.setFinsAccessoryDistribution(
      {{"NoFins", 0.5}, {"WithFins", 0.5}}); // Half with fins
  env.setShellAccessoryDistribution(
      {{"NoShell", 1.0}, {"WithShell", 0.0}}); // No need for shells

  // 4. Configure behavior distribution
  env.setBehaviorDistribution({{"Anticipating", 0.0},
                               {"Fearfull", 0.0},
                               {"Gregarious", 1.0},
                               {"Kamikaze", 0.0},
                               {"MultiPersonality", 0.0}});

  // 5. Run the simulation
  ecosystem.run();
}