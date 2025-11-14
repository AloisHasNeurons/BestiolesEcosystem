#ifndef GREGARIOUS_H
#define GREGARIOUS_H

#include "../interfaces/IBehavior.h"

class Gregarious : public IBehavior {
 public:
  double& steer(double orientation) override;
};

#endif  // GREGARIOUS_H