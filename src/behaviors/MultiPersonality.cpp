#include "behaviors/MultiPersonality.h"

#include <chrono>
#include <cstdlib>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "interfaces/IBestiole.h"

MultiPersonality::MultiPersonality() {
  // Initialize with a random behavior
  int behaviorType = rand() % 4;
  switch (behaviorType) {
    case 0:
      // Fearful(int max_neighbors)
      currentBehavior = new Fearful(rand() % 5 + 4);
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
    default:
      currentBehavior = new Kamikaze();  // Safe fallback
      break;
  }
  lastChange = std::chrono::steady_clock::now();
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
  if (now - lastChange > std::chrono::seconds(4)) {  // Time-based change
    int behaviorType = rand() % 4;

    delete currentBehavior;  // Free the old behavior

    switch (behaviorType) {
      case 0:
        currentBehavior = new Fearful(rand() % 5 + 4);
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