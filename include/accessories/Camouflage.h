#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include "../interfaces/IAccessory.h"

class Camouflage : public IAccessory {
public:
  explicit Camouflage(IBestiole *b);
  ~Camouflage() override = default;

  void action(Environment &env) override;
  void draw(UImg &img) override;
  std::vector<std::string> getAccessories() const override {
    std::vector<std::string> accessories = m_bestiole->getAccessories();
    accessories.push_back("Camouflage");
    return accessories;
  }
  double getCamouflage() const override;

private:
  double m_psi;
};

#endif // CAMOUFLAGE_H