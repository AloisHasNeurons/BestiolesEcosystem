#ifndef FEARFUL_H
#define FEARFUL_H

#include "../interfaces/IBehavior.h"
#include <vector>

class IBestiole;

class Fearful : public IBehavior {
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  Fearful(int max_neighbors) : max_neighbors(max_neighbors) {};

 private:
  int max_neighbors;
};

#endif  // FEARFUL_H