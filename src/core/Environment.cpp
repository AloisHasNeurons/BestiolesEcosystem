#include "core/Environment.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>

#include "UImg.h"
#include "core/Bestiole.h"
#include "patterns/Factory.h"

// Define static members (using 'k' prefix)

// Color array for the environment background (white: 255, 255, 255).
const unsigned char Environment::kBackgroundColor[] = {255, 255, 255};
// The probability of a new bestiole being born in a step.
double Environment::kBirthRateProbability = 0.1;
// Minimum angle difference for the bestiole's eye orientation check.
double Environment::kDeltaEyeMinRadians = 0.0;
// Maximum angle difference for the bestiole's eye orientation check (90
// degrees).
double Environment::kDeltaEyeMaxRadians = M_PI / 2;
// Angle parameter related to eye perception (45 degrees).
double Environment::kAlphaRadians = M_PI / 4;
// Minimum eye distance/range parameter.
double Environment::kGammaEyeMinPixels = 0.0;
// Maximum eye distance/range parameter.
double Environment::kGammaEyeMaxPixels = 20.0;

/**
 * @brief Constructs an Environment with specified dimensions and a factory.
 *
 * Initializes the environment dimensions and sets up the random number
 * generator.
 * @param kWidth The width of the environment (in pixels).
 * @param kHeight The height of the environment (in pixels).
 * @param factoryRef The factory used to create IBestiole objects.
 */
Environment::Environment(int kWidth, int kHeight, IFactory& factoryRef)
    : UImg(kWidth, kHeight, 1, 3), m_factory(factoryRef), m_stepCount(0) {
  m_lastSummaryTime = std::chrono::steady_clock::now();
  // Initialize the random number generator seed.
  std::srand(time(NULL));
}

/**
 * @brief Constructs an Environment with default dimensions and a factory.
 *
 * Uses default dimensions from UImg (usually 640x480) and sets up the random
 * number generator.
 * @param factoryRef The factory used to create IBestiole objects.
 */
Environment::Environment(IFactory& factoryRef)
    : m_factory(factoryRef), m_stepCount(0) {
  m_lastSummaryTime = std::chrono::steady_clock::now();
  // Initialize the random number generator seed.
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

  // Iterate over all bestioles and delete them to free memory.
  for (std::vector<IBestiole*>::iterator iterator = m_bestiolesList.begin();
       iterator != m_bestiolesList.end(); ++iterator) {
    delete (*iterator);
  }
  // Clear the list pointers.
  m_bestiolesList.clear();
  m_bestiolesToAdd.clear();
}

/**
 * @brief Executes one step of the environment simulation.
 *
 * Handles adding new bestioles, clearing dead ones, updating state,
 * checking for collisions, and potentially creating new bestioles.
 * @param void No parameters.
 */
void Environment::step(void) {
  // 1. Add bestioles that were created in the previous step/frame.
  for (IBestiole* bestiole : m_bestiolesToAdd) {
    m_bestiolesList.push_back(bestiole);
  }
  m_bestiolesToAdd.clear();

  // 2. Remove dead bestioles (lifespan < 0).
  auto iterator = m_bestiolesList.begin();
  while (iterator != m_bestiolesList.end()) {
    IBestiole* bestiole = (*iterator);

    // Check if the bestiole is marked for death (lifeSpan < 0).
    if (bestiole->getLifeSpan() < 0) {
      delete bestiole;  // Free memory
      iterator = m_bestiolesList.erase(
          iterator);  // Remove from list and advance iterator
    } else {
      ++iterator;  // Bestiole is alive, continue
    }
  }

  // 3. Clear the display by filling it with the background color.
  cimg_forXY(*this, x, y) fillC(x, y, 0, kBackgroundColor[0],
                                         kBackgroundColor[1],
                                         kBackgroundColor[2]);

  // 4. Iterate through all bestioles to update, draw, and check collisions.
  for (auto currentBestiole : m_bestiolesList) {
    // a. Executes the bestiole's action (movement/behavior).
    currentBestiole->action(*this);
    // b. Draws the bestiole on the environment.
    currentBestiole->draw(*this);

    // c. Collision check against all other bestioles.
    for (std::vector<IBestiole*>::iterator collisionIterator =
             m_bestiolesList.begin();
         collisionIterator != m_bestiolesList.end(); ++collisionIterator) {
      IBestiole* otherBestiole = (*collisionIterator);

      // Skip checking collision with itself.
      if (currentBestiole == otherBestiole) continue;

      // Calculate distance between the two bestioles.
      double dx = currentBestiole->getX() - otherBestiole->getX();
      double dy = currentBestiole->getY() - otherBestiole->getY();
      double dist = std::sqrt(dx * dx + dy * dy);

      // Define the distance for considering a collision (using
      // Bestiole::kAffSizePixels * factor).
      const double kCollisionThreshold = 8.0;

      if (dist < kCollisionThreshold) {
        // Trigger the bestiole's collision behavior.
        if (currentBestiole->collision()) {
          recordEvent(otherBestiole->getBehaviorString() + " killed " +
                      currentBestiole->getBehaviorString());
        }
      }
    }
  }

  // 5. Check for birth chance.
  // Generate a random double between 0.0 and 1.0.
  double randomValue =
      static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX) + 1.0);

  // Check if a new bestiole should be born based on kBirthRateProbability.
  if (randomValue < kBirthRateProbability) {
    // Create a new bestiole using the factory.
    IBestiole* newBestiole = m_factory.createBestiole();
    if (newBestiole) {
      // Add the new bestiole to the environment (m_bestiolesToAdd list).
      this->addMember(newBestiole);
      recordEvent("Birth of " + newBestiole->getBehaviorString());
    }
  }

  // 6. Track statistics
  m_stepCount++;
  auto now = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed = now - m_lastSummaryTime;

  if (elapsed.count() >= m_summaryIntervalSeconds) {
    m_statsCollector.track(m_bestiolesList, m_stepCount);
    m_lastSummaryTime = now;
  }
}

/**
 * @brief Adds a new IBestiole member to the environment.
 *
 * The new member is added to a temporary list to be incorporated in the next
 * step, and its initial coordinates are set.
 * @param bestiole A pointer to the IBestiole to add (renamed from 'b').
 */
void Environment::addMember(IBestiole* bestiole) {
  this->m_bestiolesToAdd.push_back(bestiole);  // Add bestiole to the list
  // Initialize the bestiole's coordinates within the environment bounds.
  bestiole->initCoords(this->width(), this->height());
}

/**
 * @brief Counts the number of neighboring bestioles that the given bestiole
 * can see.
 *
 * Iterates through all other bestioles and checks if the given bestiole's
 * perception allows it to see the other bestiole.
 * @param currentBestiole The bestiole whose neighbors are being counted
 * (renamed from 'b').
 * @return The number of neighboring bestioles visible to `currentBestiole`.
 */
int Environment::neighborCount(const IBestiole& currentBestiole) {
  int neighborCount = 0;
  // Iterate through all bestioles in the environment.
  for (std::vector<IBestiole*>::iterator iterator = m_bestiolesList.begin();
       iterator != m_bestiolesList.end(); ++iterator) {
    IBestiole* otherBestiole = (*iterator);

    // Skip checking itself as a neighbor.
    if (&currentBestiole == otherBestiole) continue;

    // Check if the current bestiole can perceive the other bestiole.
    if (currentBestiole.canSee(*otherBestiole)) {
      ++neighborCount;
    }
  }
  return neighborCount;
}

void Environment::recordEvent(const std::string& event) {
  m_statsCollector.addEvent(event);
}

/**
 * @brief Retrieves the distribution probabilities of the defined behaviors.
 *
 * Extracts the probability values from the internal behavior distribution map.
 * @return A vector of doubles representing the probabilities of different
 * behaviors.
 */
std::vector<double> Environment::getBehaviorDistribution() const {
  std::vector<double> probabilities;
  // Iterate through the map and extract the probability (second element of the
  // pair).
  for (const auto& pair : m_behaviorDistribution) {
    probabilities.push_back(pair.second);
  }
  return probabilities;
}