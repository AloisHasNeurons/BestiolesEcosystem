#include "behaviors/Anticipating.h"

#include <cmath>
#include <limits>  // Added for numeric_limits

#include "interfaces/IBestiole.h"

double Anticipating::steer(IBestiole& b,
                           std::vector<IBestiole*> bestiolesList) {
  double closest_distance = std::numeric_limits<double>::max();
  IBestiole* closest_bestiole = nullptr;
  // search for the closest bestiole
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* autre = (*it);
    if (&b != autre && b.canSee(*autre)) {
      double distance =
          std::sqrt((b.getX() - autre->getX()) * (b.getX() - autre->getX()) +
                    (b.getY() - autre->getY()) * (b.getY() - autre->getY()));
      if (distance < closest_distance) {
        closest_distance = distance;
        closest_bestiole = autre;
      }
    }
  }

  if (!closest_bestiole) {
    return b.getOrientation();
  }

  // estimate future position of the closest bestiole
  double future_y = -sin(closest_bestiole->getOrientation()) *
                        (closest_bestiole->getSpeed()) +
                    closest_bestiole->getY();
  double future_x =
      cos(closest_bestiole->getOrientation()) * (closest_bestiole->getSpeed()) +
      closest_bestiole->getX();
  // estimate future position of the current bestiole
  double b_future_y = -sin(b.getOrientation()) * (b.getSpeed()) + b.getY();
  double b_future_x = cos(b.getOrientation()) * (b.getSpeed()) + b.getX();
  // compute the future distance
  double future_distance =
      std::sqrt((b_future_x - future_x) * (b_future_x - future_x) +
                (b_future_y - future_y) * (b_future_y - future_y));
  // compute the anticipated orientation depending on this evolution of the
  // distance
  double anticipated_orientation;
  if (future_distance < closest_distance) {
    anticipated_orientation =
        closest_bestiole->getOrientation() +
        M_PI;  // avoid potential collision by passing parallel to this bestiole
  } else {
    anticipated_orientation = b.getOrientation();  // keep current orientation
  }
  return anticipated_orientation;
}

// [Fix] Implementation added to satisfy linker
double Anticipating::speed(IBestiole& b,
                           std::vector<IBestiole*> bestiolesList) {
  return b.getSpeed();
}