#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "../interfaces/IBehavior.h"

class Bestiole;

class Kamikaze : public IBehavior {
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
};

#endif  // KAMIKAZE_H