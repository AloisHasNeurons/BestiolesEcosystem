#ifndef GREGARIOUS_H
#define GREGARIOUS_H

#include "../interfaces/IBehavior.h"
#include <vector>

class IBestiole;

class Gregarious : public IBehavior {
 public:
  double& steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
};

#endif  // GREGARIOUS_H 