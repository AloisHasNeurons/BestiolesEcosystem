#include "patterns/Factory.h"

#include <random>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"
#include "core/Bestiole.h"
#include "core/Environment.h"  // Need full definition here for env->getBehaviorDistribution

Factory::Factory() : env(nullptr) {}

void Factory::setEnvironment(const Environment* e) { env = e; }

IBestiole* Factory::createBestiole() {
  if (!env) return nullptr;  // Safety check

  auto probs = env->getBehaviorDistribution();

  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::discrete_distribution<int> dist(probs.begin(), probs.end());

  int choice = dist(gen);
  std::unique_ptr<IBehavior> behavior;

  switch (choice) {
    case 0:
      behavior = std::unique_ptr<Anticipating>(new Anticipating());
      break;
    case 1:
      behavior = std::unique_ptr<Fearful>(new Fearful());
      break;
    case 2:
      behavior = std::unique_ptr<Gregarious>(new Gregarious());
      break;
    case 3:
      behavior = std::unique_ptr<Kamikaze>(new Kamikaze());
      break;
    case 4:
      behavior = std::unique_ptr<MultiPersonality>(new MultiPersonality());
      break;
    default:
      behavior = std::unique_ptr<Kamikaze>(new Kamikaze());
      break;
  }

  return new Bestiole(std::move(behavior));
}