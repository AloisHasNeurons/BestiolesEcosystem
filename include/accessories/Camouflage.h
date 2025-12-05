#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "../interfaces/IAccessory.h"

class Camouflage : public IAccessory {
public:
  explicit Camouflage(IBestiole *b);
  ~Camouflage() override = default;

  void action(Environment &env, IBestiole* self) override;
  void draw(UImg &img) override;
  std::string getDescription() const override;
  virtual IBestiole *clone() override;

  double getCamouflage() const override;

private:
  double m_psi;
};

#endif // CAMOUFLAGE_H