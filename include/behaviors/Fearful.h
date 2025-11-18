#ifndef FEARFUL_H
#define FEARFUL_H

#include "../interfaces/IBehavior.h"
#include <vector>

class IBestiole;

class Fearful : public IBehavior {
 public:
  double& steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double accelerate(bool isClose);

 private:
  int max_neighbors;
};

#endif  // FEARFUL_H