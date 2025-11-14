#ifndef ANTICIPATING_H
#define ANTICIPATING_H

#include "../interfaces/IBehavior.h"

class Anticipating : public IBehavior {
 public:
  double& steer(double orientation) override;
};

#endif  // ANTICIPATING_H