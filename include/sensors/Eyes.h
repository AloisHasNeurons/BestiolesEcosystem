#ifndef EYES_H
#define EYES_H

#include "../interfaces/ISensor.h"

class Eyes : public ISensor {
 public:
  bool Detect(IBestiole& b) override;
  void draw() override;

 private:
  double delta;
  double alpha;
  double gamma;
};

#endif  // EYES_H