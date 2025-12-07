#include "behaviors/Anticipating.h"

#include <cmath>
#include <limits>  // Added for numeric_limits
#include <vector>

#include "interfaces/IBestiole.h"

/**
 * @brief Calculates the steering force/direction for the Anticipating bestiole.
 *
 * This method finds the closest bestiole and determines the steering
 * orientation based on whether the distance between the two bestioles is
 * anticipated to increase or decrease in the next step.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated steering adjustment (orientation in radians).
 */
double Anticipating::steer(IBestiole* currentBestiole,
                           std::vector<IBestiole*> otherBestioles) {
  double closest_distance = std::numeric_limits<double>::max();
  IBestiole* closest_bestiole = nullptr;

  // Search for the closest visible bestiole.
  for (std::vector<IBestiole*>::const_iterator it = otherBestioles.begin();
       it != otherBestioles.end(); ++it) {
    IBestiole* other = (*it);
    // Check if it's not the same bestiole and if it's visible.
    if (currentBestiole != other && (currentBestiole->canSee(*other)
                                  || currentBestiole->canHear(*other))) {
      // Calculate the current distance.
      double distance = std::sqrt((currentBestiole->getX() - other->getX()) *
                                  (currentBestiole->getX() - other->getX()) +
                                  (currentBestiole->getY() - other->getY()) *
                                  (currentBestiole->getY() - other->getY()));

      if (distance < closest_distance) {
        closest_distance = distance;
        closest_bestiole = other;
      }
    }
  }

  if (!closest_bestiole) {
    // If no visible bestiole is found, maintain the current orientation.
    return currentBestiole->getOrientation();
  }

  // --- Start Anticipation Logic ---

  // Estimate future position of the closest bestiole (assuming one step
  // forward).
  double future_y = -sin(closest_bestiole->getOrientation()) *
                        (closest_bestiole->getSpeed()) +
                    closest_bestiole->getY();
  double future_x =
      cos(closest_bestiole->getOrientation()) * (closest_bestiole->getSpeed()) +
      closest_bestiole->getX();

  // Estimate future position of the current bestiole (assuming one step
  // forward).
  double current_future_y =
      -sin(currentBestiole->getOrientation()) * (currentBestiole->getSpeed()) +
      currentBestiole->getY();
  double current_future_x =
      cos(currentBestiole->getOrientation()) * (currentBestiole->getSpeed()) +
      currentBestiole->getX();
  // Compute the future distance between the two bestioles.
  double future_distance =
      std::sqrt((current_future_x - future_x) * (current_future_x - future_x) +
                (current_future_y - future_y) * (current_future_y - future_y));

  // Compute the anticipated orientation depending on the evolution of the
  // distance.
  double anticipated_orientation;
  if (future_distance < closest_distance) {
    // If the distance is decreasing (potential collision/closing gap), steer
    // away. M_PI is added to turn 180 degrees relative to the closest
    // bestiole's orientation to pass parallel to it (avoiding a head-on
    // collision or close approach).
    anticipated_orientation = closest_bestiole->getOrientation() + M_PI;
  } else {
    // If the distance is stable or increasing, keep the current orientation.
    anticipated_orientation = currentBestiole->getOrientation();
  }
  return anticipated_orientation;
}

/**
 * @brief Calculates the speed for the Anticipating bestiole.
 *
 * Currently returns the bestiole's current speed. Behavior could be extended
 * to accelerate or decelerate based on anticipation.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated speed value.
 */
double Anticipating::speed(IBestiole* currentBestiole,
                           std::vector<IBestiole*> otherBestioles) {
  return currentBestiole->getSpeed();
}