#include "Gregarious.h"
#include "IBestiole.h"

double& Gregarious::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  std::vector<double> orientations;
  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* autre = (*it);
    if (b.canSee(*autre) && &b != autre) {
    orientations.push_back(autre->getOrientation());
    }}
  double sum = 0.0;
  for (double ori : orientations) {
    sum += ori;
  }
  double average_orientation = sum / orientations.size();
  return average_orientation;
}