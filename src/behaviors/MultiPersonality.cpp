#include "behaviors/MultiPersonality.h"

#include <chrono>
#include <cstdlib>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "interfaces/IBestiole.h"

MultiPersonality::MultiPersonality() {
  currentBehavior = new Kamikaze();  // Default behavior to start
}

double MultiPersonality::steer(IBestiole& b,
                               std::vector<IBestiole*> bestiolesList) {
  changeBehavior();
  return currentBehavior->steer(b, bestiolesList);
}

double MultiPersonality::speed(IBestiole& b,
                               std::vector<IBestiole*> bestiolesList) {
  return currentBehavior->speed(b, bestiolesList);
}

void MultiPersonality::changeBehavior() {
  auto now = std::chrono::steady_clock::now();
  if (now - lastChange >
      std::chrono::seconds(4)) {  // time based behavioral change
    int behaviorType = rand() % 4;
    delete currentBehavior;  // Free the memory of the old behavior
    switch (behaviorType) {
      case 0:
        currentBehavior = new Fearful(
            rand() % 5 + 4);  // Random max_neighbors between 4 and 8
        break;
      case 1:
        currentBehavior = new Gregarious();
        break;
      case 2:
        currentBehavior = new Kamikaze();
        break;
      case 3:
        currentBehavior = new Anticipating();
        break;
    }
    lastChange = now;
  }
}

MultiPersonality::~MultiPersonality() { delete currentBehavior; }