#include "core/Environment.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "core/Bestiole.h"
#include "patterns/Factory.h"

// Define static members

// Color array for the environment background (white: 255, 255, 255).
const unsigned char Environment::white[] = {255, 255, 255};
// The probability of a new bestiole being born in a step.
double Environment::birthRate = 0.1;
// Minimum angle difference for the bestiole's eye orientation check.
double Environment::deltaEyeMin = 0.0;
// Maximum angle difference for the bestiole's eye orientation check (90
// degrees).
double Environment::deltaEyeMax = M_PI / 2;
// Angle parameter related to eye perception (45 degrees).
double Environment::alpha = M_PI / 4;
// Minimum eye distance/range parameter.
double Environment::gammaEyeMin = 0.0;
// Maximum eye distance/range parameter.
double Environment::gammaEyeMMax = 20.0;

/**
 * @brief Constructs an Environment with specified dimensions and a factory.
 *
 * Initializes the environment dimensions and sets up the random number
 * generator.
 * @param _width The width of the environment (in pixels).
 * @param _height The height of the environment (in pixels).
 * @param f The factory used to create IBestiole objects.
 */
Environment::Environment(int _width, int _height, IFactory& f)
    : UImg(_width, _height, 1, 3), factory(f) {
  std::cout << "const Environment" << std::endl;
  std::srand(time(NULL));
}

/**
 * @brief Constructs an Environment with default dimensions and a factory.
 *
 * Uses default dimensions from UImg (usually 640x480) and sets up the random
 * number generator.
 * @param f The factory used to create IBestiole objects.
 */
Environment::Environment(IFactory& f) : factory(f) {
  std::cout << "const Environment" << std::endl;
  std::srand(time(NULL));
}

/**
 * @brief Destroys the Environment object.
 *
 * Deletes all IBestiole objects currently in the environment and clears the
 * lists.
 * @param void No parameters.
 */
Environment::~Environment(void) {
  std::cout << "dest Environment" << std::endl;

  // Iterate over all bestioles and delete them.
  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    delete (*it);
  }
  // Clear the list pointers.
  bestiolesList.clear();
  bestiolesToAdd.clear();
}

/**
 * @brief Executes one step of the environment simulation.
 *
 * In each step:
 * 1. Adds newly created bestioles to the main list.
 * 2. Clears the display by filling it with the background color (white).
 * 3. Iterates through all bestioles:
 *    a. Executes the bestiole's action (movement/behavior).
 *    b. Draws the bestiole on the environment.
 *    c. Checks for collisions with every other bestiole.
 * 4. Checks the birth rate probability and creates a new bestiole if the
 *    condition is met.
 * @param void No parameters.
 */
void Environment::step(void) {
  // Add bestioles that were created in the previous step/frame.
  for (IBestiole* b : bestiolesToAdd) {
    bestiolesList.push_back(b);
  }
  bestiolesToAdd.clear();

  auto it = bestiolesList.begin();
  while (it != bestiolesList.end()) {
    IBestiole* b = (*it);

    if (b->getLifeSpan() < 0) {
      delete b;
      it = bestiolesList.erase(it);
    } else {
      ++it;
    }
  }

  cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

  for (auto b : bestiolesList) {
    b->action(*this);
    // Draw the bestiole on the environment.
    b->draw(*this);

    // Collision check against all other bestioles.
    for (std::vector<IBestiole*>::iterator it2 = bestiolesList.begin();
         it2 != bestiolesList.end(); ++it2) {
      IBestiole* other = (*it2);

      // Skip checking collision with itself.
      if (b == other) continue;

      // Calculate distance between the two bestioles.
      double dx = b->getX() - other->getX();
      double dy = b->getY() - other->getY();
      double dist = std::sqrt(dx * dx + dy * dy);

      // Define the distance for considering a collision.
      double collisionThreshold = 8.0;

      if (dist < collisionThreshold) {
        // Trigger the bestiole's collision behavior.
        b->collision();
      }
    }
  }

  // Generate a random double between 0.0 and 1.0.
  double randomValue =
      static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX) + 1.0);

  // Check if a new bestiole should be born based on birthRate.
  if (randomValue < birthRate) {
    // Create a new bestiole using the factory.
    IBestiole* newBestiole = factory.createBestiole();
    if (newBestiole) {
      // Add the new bestiole to the environment.
      this->addMember(newBestiole);
    }
  }
}

/**
 * @brief Adds a new IBestiole member to the environment.
 *
 * The new member is added to a temporary list to be incorporated in the next
 * step, and its initial coordinates are set.
 * @param b A pointer to the IBestiole to add.
 */
void Environment::addMember(IBestiole* b) {
  this->bestiolesToAdd.push_back(b);  // Add bestiole to the list
  // Initialize the bestiole's coordinates within the environment bounds.
  b->initCoords(this->width(), this->height());
}

/**
 * @brief Counts the number of neighboring bestioles that the given bestiole
 * can see.
 *
 * Iterates through all other bestioles and checks if the given bestiole's
 * perception allows it to see the other bestiole.
 * @param b The bestiole whose neighbors are being counted.
 * @return The number of neighboring bestioles visible to `b`.
 */
int Environment::neighborCount(const IBestiole& b) {
  int nb = 0;
  // Iterate through all bestioles in the environment.
  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it);

    // Skip checking itself as a neighbor.
    if (&b == other) continue;

    // Check if the current bestiole can perceive the other bestiole.
    if (b.canSee(*other)) {
      ++nb;
    }
  }
  return nb;
}

/**
 * @brief Retrieves the distribution probabilities of the defined behaviors.
 *
 * Extracts the probability values from the internal behavior distribution map.
 * @return A vector of doubles representing the probabilities of different
 * behaviors.
 */
std::vector<double> Environment::getBehaviorDistribution() const {
  std::vector<double> probs;
  // Iterate through the map and extract the probability (second element of the
  // pair).
  for (const auto& pair : behaviorDistribution) {
    probs.push_back(pair.second);
  }
  return probs;
}
