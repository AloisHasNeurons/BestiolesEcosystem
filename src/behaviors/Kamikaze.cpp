#include "behaviors/Kamikaze.h"

#include <cmath>
#include <limits>

#include "interfaces/IBestiole.h"

double Kamikaze::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  double closest_distance = std::numeric_limits<double>::max();
  IBestiole* closest_bestiole = nullptr;
  // search for the closest bestiole
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it);
    if (&b != other && b.canSee(*other)) {
      double distance =
          std::sqrt((b.getX() - other->getX()) * (b.getX() - other->getX()) +
                    (b.getY() - other->getY()) * (b.getY() - other->getY()));
      if (distance < closest_distance) {
        closest_distance = distance;
        closest_bestiole = other;
      }
    }
  }

  if (closest_bestiole) {
    double adjusted_orientation =
        std::atan2(-(closest_bestiole->getY() - b.getY()),
                   closest_bestiole->getX() - b.getX());
    return adjusted_orientation;
  } else {
    return b.getOrientation();
  }
}

// [Fix] Implementation added to satisfy linker
double Kamikaze::speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  return b.getSpeed();
}