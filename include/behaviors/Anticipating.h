#ifndef ANTICIPATING_H
#define ANTICIPATING_H

#include "../interfaces/IBehavior.h"
#include <vector>
class IBestiole;

class Anticipating : public IBehavior {
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
};

#endif  // ANTICIPATING_H