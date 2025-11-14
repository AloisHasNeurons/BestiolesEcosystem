#ifndef GREGAIRE_H
#define GREGAIRE_H

#include "../interfaces/IComportement.h"

class Gregaire : public IComportement {
 public:
  double& diriger(double orientation) override;
};

#endif  // GREGAIRE_H