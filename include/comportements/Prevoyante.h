#ifndef PREVOYANTE_H
#define PREVOYANTE_H

#include "../interfaces/IComportement.h"

class Prevoyante : public IComportement {
 public:
  double& diriger(double orientation) override;
};

#endif  // PREVOYANTE_H