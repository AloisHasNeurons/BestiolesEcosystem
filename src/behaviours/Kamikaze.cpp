#include "behaviours/Kamikaze.h"
#include "interfaces/IBestiole.h"
#include <limits>
#include <cmath>

double Kamikaze::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  double closest_distance = std::numeric_limits<double>::max();
  IBestiole* closest_bestiole = nullptr;
  // search for the closest bestiole
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* autre = (*it);
    if (&b != autre && b.canSee(*autre)) {
      double distance = std::sqrt((b.getX() - autre->getX()) * (b.getX() - autre->getX()) +
                                  (b.getY() - autre->getY()) * (b.getY() - autre->getY()));
      if (distance < closest_distance) {
        closest_distance = distance;
        closest_bestiole = autre;
      }
    }
  }

  if (closest_bestiole) {
    double adjusted_orientation = std::atan2(-(closest_bestiole->getY() - b.getY()),
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