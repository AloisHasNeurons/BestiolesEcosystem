#include <iostream>
#include <memory> // Required for std::unique_ptr

#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"

// Include behavior headers
#include "behaviors/MultiPersonality.h"

void run_test_multipersonality_behavior() {
  Aquarium ecosystem(640, 480, 30);

  ecosystem.getEnvironment().setBehaviorDistribution(
      {{"Gregarious", 0.0},
       {"Fearful", 0.0},
       {"Kamikaze", 0.0},
       {"Anticipating", 0.0},
       {"MultiPersonality", 1.0}});

  ecosystem.getEnvironment().setEyesAccessoryDistribution(
      {{"NoEyes", 0.0}, {"WithEyes", 1.0}});

  ecosystem.getEnvironment().setEarsAccessoryDistribution(
      {{"NoEars", 1.0}, {"WithEars", 0.0}});

  ecosystem.getEnvironment().setCamouflageAccessoryDistribution(
      {{"NoCamouflage", 1.0}, {"WithCamouflage", 0.0}});

  ecosystem.getEnvironment().setFinsAccessoryDistribution(
      {{"NoFins", 1.0}, {"WithFins", 0.0}});

  ecosystem.getEnvironment().setShellAccessoryDistribution(
      {{"NoShell", 1.0}, {"WithShell", 0.0}});

  ecosystem.run();
}