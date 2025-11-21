#include "behaviors/Gregarious.h"
#include "interfaces/IBestiole.h"

double Gregarious::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  std::vector<double> orientations;
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it);
    if (b.canSee(*other) && &b != other) {
    orientations.push_back(other->getOrientation());
    }}
  double sum = 0.0;
  for (double ori : orientations) {
    sum += ori;
  }
  if (orientations.empty()) {
    return b.getOrientation();
  }
  double average_orientation = sum / orientations.size();
  return average_orientation;
}

// [Fix] Implementation added to satisfy linker
double Gregarious::speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  return b.getSpeed();
}