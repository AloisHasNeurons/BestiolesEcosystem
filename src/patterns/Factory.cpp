#include "patterns/Factory.h"

#include <random>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"
#include "core/Bestiole.h"
#include "core/Environment.h"  // Need full definition here for env->getBehaviorDistribution

/**
 * @brief Constructs a Factory object.
 *
 * Initializes the environment pointer to nullptr.
 */
Factory::Factory() : env(nullptr) {}

/**
 * @brief Sets the environment reference for the factory.
 *
 * The factory needs access to the environment to retrieve the current
 * behavior distribution when creating new bestioles.
 *
 * @param e A pointer to the Environment instance.
 */
void Factory::setEnvironment(const Environment* e) { env = e; }

/**
 * @brief Creates a new Bestiole with a behavior selected based on the
 * environment's distribution.
 *
 * Uses a weighted random selection (discrete distribution) to choose a behavior
 * type and then instantiates a Bestiole with that specific behavior.
 *
 * @return A pointer to the newly created IBestiole, or nullptr if the
 * environment is not set.
 */
IBestiole* Factory::createBestiole() {
  if (!env) return nullptr;  // Safety check

  // Get the probabilities for each behavior from the environment.
  auto probs = env->getBehaviorDistribution();

  // Setup static random number generation components.
  static std::random_device rd;
  static std::mt19937 gen(rd());
  // Create a discrete distribution based on the provided probabilities.
  std::discrete_distribution<int> dist(probs.begin(), probs.end());

  // Select the behavior index based on the weighted distribution.
  int choice = dist(gen);
  std::unique_ptr<IBehavior> behavior;

  // Instantiate the chosen behavior. The index corresponds to the order in
  // which the probabilities were returned by the environment.
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
      // Fallback to a default behavior if the index is out of bounds.
      behavior = std::unique_ptr<Kamikaze>(new Kamikaze());
      break;
  }

  // Create the Bestiole, transferring ownership of the unique_ptr to it.
  return new Bestiole(std::move(behavior));
}