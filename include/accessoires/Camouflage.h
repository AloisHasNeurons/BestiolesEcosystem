#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "../interfaces/IAccessoire.h"

class Camouflage : public IAccessoire {
 public:
  void changeParam() override;
  void draw() override;

 private:
  double psi;
};

#endif  // CAMOUFLAGE_H