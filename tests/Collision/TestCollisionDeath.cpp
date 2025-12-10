#include <iostream>
#include <map>
#include <string>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_death_by_collision() {
  std::cout << "Running Test Scenario: Death by Collision" << std::endl;
  std::cout << "Observation: Kamikaze & Gregarious. Collisions = Death. Births "
               "enabled."
            << std::endl;

  // Configure Eyes (strong vision)
  SensorConfig eyeCfg;
  eyeCfg.deltaMin = 20.0; eyeCfg.deltaMax = 30.0;
  eyeCfg.alphaMin = 360.0; eyeCfg.alphaMax = 360.0;
  eyeCfg.gammaMin = 1.0; eyeCfg.gammaMax = 1.0;
  Aquarium::setEyeConfig(eyeCfg);

  // Setup Aquarium and Environment
  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();
  Bestiole::setStartCloneRate(0.0);
  Bestiole::setStartResistance(0.0); // Vulnerable

  env.resetPopulation();
  // Enable birth
  env.setBirthRateProbability(0.05);

  std::map<std::string, double> dist;
  dist["Kamikaze"] = 0.7;
  dist["Gregarious"] = 0.3;
  dist["Fearfull"] = 0.0;
  dist["Anticipating"] = 0.0;
  dist["MultiPersonality"] = 0.0;
  env.setBehaviorDistribution(dist);

  env.setShellAccessoryDistribution(
      {{"WithShell", 0.0}, {"NoShell", 1.0}}); // No shell to obsorve death
  env.setEyesAccessoryDistribution(
      {{"WithEyes", 1.0},
       {"NoEyes", 0.0}}); // Eyes needed for collision
  env.setCamouflageAccessoryDistribution(
      {{"WithCamouflage", 0.0},
       {"NoCamouflage", 1.0}}); // No need for camouflage
  env.setEarsAccessoryDistribution(
      {{"WithEars", 0.0}, {"NoEars", 1.0}}); // No need for ears
  env.setFinsAccessoryDistribution(
      {{"WithFins", 0.0}, {"NoFins", 1.0}}); // No need for fins

  env.spawnPopulation(30);

  // Using static resistance

  ecosystem.run();
  Bestiole::setStartCloneRate(-1.0);
  Bestiole::setStartResistance(-1.0);
}
