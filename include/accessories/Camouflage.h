#ifndef CAMOUFLAGE_H
#define CAMOUFLAGE_H

#include <string>
#include <vector>

#include "../interfaces/IAccessory.h"

class Camouflage : public IAccessory {
public:
  explicit Camouflage(IBestiole *b);
  Camouflage(const Camouflage &other, IBestiole *inner);
  ~Camouflage() override = default;

  IBestiole *clone() override;

  void action(Environment &env, IBestiole *self = nullptr) override;
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