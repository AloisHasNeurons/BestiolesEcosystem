#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "../interfaces/IBehavior.h"

class Bestiole;

class Kamikaze : public IBehavior {
 public:
  double& steer(double orientation) override;
  Bestiole closestNeighbor();  // Note: returns by copy
};

#endif  // KAMIKAZE_H