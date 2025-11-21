#include "behaviors/Gregarious.h"

#include "interfaces/IBestiole.h"

double Gregarious::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  std::vector<double> positionsX, positionsY; // Positions of visible bestioles
  for (std::vector<IBestiole*>::const_iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* autre = (*it);
    if (b.canSee(*autre) && &b != autre) { // If b can see autre and they are not the same bestiole
      positionsX.push_back(autre->getX());
      positionsY.push_back(autre->getY());
    } 
  }
  double sumX = 0.0; // Sum of X positions
  double sumY = 0.0; // Sum of Y positions
  for (size_t i = 0; i < positionsX.size(); ++i) {
    sumX += positionsX[i];
    sumY += positionsY[i];
  }
  if (positionsX.empty()) {
    return b.getOrientation(); // No visible bestioles, maintain current orientation
  }
  double avgX = sumX / positionsX.size();
  double avgY = sumY / positionsY.size();
  // Angle towards average position
  double desiredOrientation = std::atan2(avgY - b.getY(), avgX - b.getX());
  return desiredOrientation;
}

// [Fix] Implementation added to satisfy linker
double Gregarious::speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
  return b.getSpeed();
}