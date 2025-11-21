#include "behaviors/MultiPersonality.h"

#include <chrono>
#include <cstdlib>
#include <utility>
#include <vector>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "interfaces/IBestiole.h"

/**
 * @brief Default constructor for MultiPersonality.
 *
 * Initializes the bestiole with a randomly selected initial behavior
 * and sets the initial time of the last behavior change.
 */
MultiPersonality::MultiPersonality() {
  int behaviorType = rand() % 4;
  switch (behaviorType) {
    case 0:
      // Randomly initialize Fearful with max_neighbors between 4 and 8
      // (inclusive)
      m_currentBehavior = new Fearful(rand() % 5 + 4);
      break;
    case 1:
      m_currentBehavior = new Gregarious();
      break;
    case 2:
      m_currentBehavior = new Kamikaze();
      break;
    case 3:
      m_currentBehavior = new Anticipating();
      break;
    default:
      m_currentBehavior = new Kamikaze();  // Safe fallback
      break;
  }
  m_lastChange = std::chrono::steady_clock::now();
}

/**
 * @brief Calculates the steering force/direction by deferring to the current
 * active behavior.
 *
 * This method first checks if the behavior needs to be changed
 * (`changeBehavior`) and then calls the `steer` method of the active behavior
 * object.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated steering adjustment (orientation in radians).
 */
double MultiPersonality::steer(IBestiole& currentBestiole,
                               std::vector<IBestiole*> otherBestioles) {
  changeBehavior();
  return m_currentBehavior->steer(currentBestiole, otherBestioles);
}

/**
 * @brief Calculates the speed by deferring to the current active behavior.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated speed value.
 */
double MultiPersonality::speed(IBestiole& currentBestiole,
                               std::vector<IBestiole*> otherBestioles) {
  return m_currentBehavior->speed(currentBestiole, otherBestioles);
}

/**
 * @brief Checks the elapsed time and potentially switches the current active
 * behavior.
 *
 * If more than 4 seconds have passed since the last change, the current
 * behavior is deleted and a new random behavior is allocated and assigned.
 */
void MultiPersonality::changeBehavior() {
  auto now = std::chrono::steady_clock::now();
  // Check if 4 seconds have elapsed since the last change.
  if (now - m_lastChange > std::chrono::seconds(4)) {
    int behaviorType = rand() % 4;

    delete m_currentBehavior;  // Free the memory of the old behavior object

    // Allocate a new random behavior object.
    switch (behaviorType) {
      case 0:
        // Randomly initialize Fearful with max_neighbors between 4 and 8
        // (inclusive)
        m_currentBehavior = new Fearful(rand() % 5 + 4);
        break;
      case 1:
        m_currentBehavior = new Gregarious();
        break;
      case 2:
        m_currentBehavior = new Kamikaze();
        break;
      case 3:
        m_currentBehavior = new Anticipating();
        break;
        // Default case is not needed here since rand() % 4 only returns 0, 1,
        // 2, or 3.
    }
    m_lastChange = now;
  }
}

/**
 * @brief Destructor for MultiPersonality.
 *
 * Ensures that the dynamically allocated current behavior object is deleted
 * to prevent memory leaks.
 */
MultiPersonality::~MultiPersonality() { delete m_currentBehavior; }