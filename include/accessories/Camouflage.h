#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "../interfaces/IAccessory.h"

class Camouflage : public IAccessory {
 public:

  Camouflage(IBestiole* b, double _psi);
  ~Camouflage() override = default;

  void action(Environment& env) override;
  void draw(UImg& img) override;

  double getCamouflage() const override;

 private:
  double psi;
};

#endif  // CAMOUFLAGE_H