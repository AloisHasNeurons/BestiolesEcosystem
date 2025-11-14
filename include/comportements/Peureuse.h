#ifndef PEUREUSE_H
#define PEUREUSE_H

#include "../interfaces/IComportement.h"

class Peureuse : public IComportement {
 public:
  double& diriger(double orientation) override;
  double accelerer(bool estProche);  // "boolean" devient "bool"

 private:
  int nb_max_voisines;
};

#endif  // PEUREUSE_H