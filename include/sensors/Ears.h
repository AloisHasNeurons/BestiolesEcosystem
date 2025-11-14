#ifndef EARS_H
#define EARS_H

#include "../interfaces/ISensor.h"

class Ears : public ISensor {
 public:
  bool Detect(IBestiole& b) override;
  void draw() override;

 private:
  double delta;
  double gamma;
};

#endif  // EARS_H