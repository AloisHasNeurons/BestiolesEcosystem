#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "../interfaces/IAccessory.h"

class Camouflage : public IAccessory {
 public:
  void updateParameters() override;
  void draw() override;

 private:
  double psi;
};

#endif  // CAMOUFLAGE_H