#ifndef FEARFUL_H
#define FEARFUL_H

#include <vector>

#include "../interfaces/IBehavior.h"

class IBestiole;

class Fearful : public IBehavior {
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;

  // [Temporary Fix] Added default value '= 1' to allow instantiation without
  // arguments
  Fearful(int max_neighbors = 1) : max_neighbors(max_neighbors) {};

 private:
  int max_neighbors;
};

#endif  // FEARFUL_H