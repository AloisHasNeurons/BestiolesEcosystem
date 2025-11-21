#ifndef FIN_H
#define FIN_H

#include "../interfaces/IAccessory.h"

class Fin : public IAccessory {
 public:
  void updateParameters() override;
  void draw() override;

 private:
  double nu;
};

#endif  // FIN_H