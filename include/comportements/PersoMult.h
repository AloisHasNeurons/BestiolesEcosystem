#ifndef PERSOMULT_H
#define PERSOMULT_H

#include "../interfaces/IComportement.h"

class PersoMult : public IComportement {
 public:
  double& diriger(double orientation) override;
  void changerComp(IComportement* newComp);
};

#endif  // PERSOMULT_H