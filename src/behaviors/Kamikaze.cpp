#include "behaviors/Kamikaze.h"

#include <cmath>
#include <limits>
#include <vector>

#include "interfaces/IBestiole.h"

/**
 * @brief Calculates the steering force/direction for the Kamikaze bestiole.
 *
 * The bestiole aggressively steers directly towards the closest visible
 * bestiole.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated steering adjustment (orientation in radians).
 */
double Kamikaze::steer(IBestiole* currentBestiole,
                       std::vector<IBestiole*> otherBestioles) {
  double closest_distance = std::numeric_limits<double>::max();
  IBestiole* closest_bestiole = nullptr;

  // Search for the closest visible bestiole.
  for (std::vector<IBestiole*>::const_iterator it = otherBestioles.begin();
       it != otherBestioles.end(); ++it) {
    IBestiole* other = (*it);
    // Check if it's not the same bestiole and if it's visible.
    if (currentBestiole != other && currentBestiole->canSee(*other)) {
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

  if (closest_bestiole) {
    double adjusted_orientation =
        std::atan2(-(closest_bestiole->getY() - currentBestiole->getY()),
                   closest_bestiole->getX() - currentBestiole->getX());
    return adjusted_orientation;
  } else {
    // If no visible bestiole is found, maintain the current orientation.
    return currentBestiole->getOrientation();
  }
}

/**
 * @brief Calculates the speed for the Kamikaze bestiole.
 *
 * Currently returns the bestiole's current speed. Behavior could be extended
 * to increase speed when a target is detected.
 *
 * @param currentBestiole The bestiole applying this behavior (renamed from
 * 'b').
 * @param otherBestioles A list of all other bestioles in the environment
 * (renamed from 'bestiolesList').
 * @return double The calculated speed value.
 */
double Kamikaze::speed(IBestiole* currentBestiole,
                       std::vector<IBestiole*> otherBestioles) {
  return currentBestiole->getSpeed();
}