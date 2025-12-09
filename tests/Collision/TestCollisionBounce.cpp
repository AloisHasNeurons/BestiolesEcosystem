#include <iostream>
#include <map>
#include <string>

#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"


void run_test_collision_bounce_no_death() {
  std::cout << "Running Test Scenario: Collision Bounce (No Death)"
            << std::endl;
  std::cout << "Observation: Kamikaze creatures bouncing off of each other with no "
               "death (Resistance=1.0)."
            << std::endl;

  Aquarium ecosystem(800, 600, 30);
  Environment &env = ecosystem.getEnvironment();
  Bestiole::setStartCloneRate(0.0);
  Bestiole::setStartResistance(1.0); // Max resistance -> No death by collision

  env.resetPopulation();

  // Kamikaze only
  std::map<std::string, double> dist;
  dist["Kamikaze"] = 1.0;
  dist["Gregarious"] = 0.0;
  dist["Fearfull"] = 0.0;
  dist["Anticipating"] = 0.0;
  dist["MultiPersonality"] = 0.0;
  env.setBehaviorDistribution(dist);


  env.setEyesAccessoryDistribution({{"WithEyes", 1.0}, {"NoEyes", 0.0}}); // Eyes needed for collision
  env.setEarsAccessoryDistribution({{"WithEars", 0.0}, {"NoEars", 1.0}});
  env.setCamouflageAccessoryDistribution({{"WithCamouflage", 0.0}, {"NoCamouflage", 1.0}});
  env.setFinsAccessoryDistribution({{"WithFins", 0.0}, {"NoFins", 1.0}});
  env.setShellAccessoryDistribution({{"WithShell", 0.0}, {"NoShell", 1.0}});

  env.spawnPopulation(20);

  // Using static resistance, no need to loop
  // auto list = env.getBestiolesList(); ...

  ecosystem.run();
  Bestiole::setStartCloneRate(-1.0);
  Bestiole::setStartResistance(-1.0);
}
