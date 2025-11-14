#ifndef FEARFUL_H
#define FEARFUL_H

#include "../interfaces/IBehavior.h"

class Fearful : public IBehavior {
 public:
  double& steer(double orientation) override;
  double accelerate(bool isClose);

 private:
  int max_neighbors;
};

#endif  // FEARFUL_H