#include "behaviors/Fearful.h"

#include <cmath>

#include "interfaces/IBestiole.h"

/**
 * @brief Calculates the steering force/direction for the Fearful bestiole.
 *
 * If the number of visible neighbors exceeds the maximum tolerance limit
 * (`m_maxNeighbors`), the bestiole turns 180 degrees to escape the crowd.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated steering adjustment (orientation in radians).
 */
double Fearful::steer(IBestiole& currentBestiole,
                      std::vector<IBestiole*> otherBestioles) {
  int visible_neighbor_count = 0;

  // Count the number of visible neighbors.
  for (std::vector<IBestiole*>::const_iterator it = otherBestioles.begin();
       it != otherBestioles.end(); ++it) {
    IBestiole* other = (*it);
    // Only count visible, distinct bestioles.
    if (currentBestiole.canSee(*other) && &currentBestiole != other) {
      visible_neighbor_count++;
    }
  }

  // Check against the maximum tolerated neighbors.
  if (visible_neighbor_count > m_maxNeighbors) {
    // If there are too many neighbors, steer away by turning 180 degrees
    // (M_PI).
    double new_orientation = currentBestiole.getOrientation() + M_PI;
    return new_orientation;
  }
  // Otherwise, maintain current orientation.
  return currentBestiole.getOrientation();
}

/**
 * @brief Calculates the speed for the Fearful bestiole.
 *
 * If the number of visible neighbors exceeds the maximum tolerance limit
 * (`m_maxNeighbors`), the bestiole increases its speed to the maximum possible
 * value.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated speed value.
 */
double Fearful::speed(IBestiole& currentBestiole,
                      std::vector<IBestiole*> otherBestioles) {
  int visible_neighbor_count = 0;

  // Count the number of visible neighbors.
  for (std::vector<IBestiole*>::const_iterator it = otherBestioles.begin();
       it != otherBestioles.end(); ++it) {
    IBestiole* other = (*it);
    // Only count visible, distinct bestioles.
    if (currentBestiole.canSee(*other) && &currentBestiole != other) {
      visible_neighbor_count++;
    }
  }

  // Check against the maximum tolerated neighbors.
  if (visible_neighbor_count > m_maxNeighbors) {
    // If there are too many neighbors, increase speed to maximum.
    return currentBestiole.getMaxSpeed();
  }
  // Otherwise, maintain normal speed.
  return currentBestiole.getSpeed();
}