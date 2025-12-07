#include "behaviors/Gregarious.h"

#include <vector>

#include "interfaces/IBestiole.h"

/**
 * @brief Calculates the steering force/direction for the Gregarious bestiole
 * (cohesion/alignment).
 *
 * The bestiole calculates the average orientation of all visible neighbors and
 * steers towards that average.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated steering adjustment (orientation in radians).
 */
double Gregarious::steer(IBestiole* currentBestiole,
                         std::vector<IBestiole*> otherBestioles) {
  std::vector<double> neighbor_orientations;

  // Collect the orientations of all visible neighbors.
  for (std::vector<IBestiole*>::const_iterator it = otherBestioles.begin();
       it != otherBestioles.end(); ++it) {
    IBestiole* other = (*it);
    // Check if it's not the same bestiole and if it's visible.
    if ((currentBestiole->canSee(*other) || currentBestiole->canHear(*other))
     && (currentBestiole != other)) {
      neighbor_orientations.push_back(other->getOrientation());
    }
  }

  // If no neighbors are visible, maintain current orientation.
  if (neighbor_orientations.empty()) {
    return currentBestiole->getOrientation();
  }

  // Calculate the sum of orientations.
  double sum = 0.0;
  for (double ori : neighbor_orientations) {
    sum += ori;
  }

  // Calculate and return the average orientation.
  double average_orientation = sum / neighbor_orientations.size();
  return average_orientation;
}

/**
 * @brief Calculates the speed for the Gregarious bestiole.
 *
 * Currently returns the bestiole's current speed. Behavior could be extended
 * to adjust speed to match neighbors (velocity matching).
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated speed value.
 */
double Gregarious::speed(IBestiole* currentBestiole,
                         std::vector<IBestiole*> otherBestioles) {
  return currentBestiole->getSpeed();
}