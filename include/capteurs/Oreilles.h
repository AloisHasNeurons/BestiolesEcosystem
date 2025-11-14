#ifndef OREILLES_H
#define OREILLES_H

#include "../interfaces/ICapteur.h"

class Oreilles : public ICapteur {
 public:
  bool Detect(IBestiole& b) override;
  void draw() override;

 private:
  double delta;
  double gamma;
};

#endif  // OREILLES_H