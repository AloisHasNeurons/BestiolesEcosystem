#ifndef YEUX_H
#define YEUX_H

#include "../interfaces/ICapteur.h"

class Yeux : public ICapteur {
 public:
  bool Detect(IBestiole& b) override;
  void draw() override;

 private:
  double delta;
  double alpha;
  double gamma;
};

#endif  // YEUX_H