#include "behaviors/Fearful.h"
#include "interfaces/IBestiole.h"
#include <cmath>

double Fearful::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  int count = 0;
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it);
    if (b.canSee(*other) && &b != other) {
      count++;
    }
    }
    if (count > max_neighbors) {
      // If there are too many neighbors, steer away
      double new_orientation = b.getOrientation() + M_PI;  // Turn around
      return new_orientation;
    }
  return b.getOrientation(); // Maintain current orientation
}

double Fearful::speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  int count = 0;
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* autre = (*it);
    if (b.canSee(*autre) && &b != autre) {
      count++;
    }
  }
  if (count > max_neighbors) {
    // If there are too many neighbors, increase speed
    return b.getMaxSpeed();
  }
  return b.getSpeed();  // Normal speed
}

