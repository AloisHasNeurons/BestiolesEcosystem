#ifndef FIN_H
#define FIN_H

#include <string>
#include <vector>

#include "../interfaces/IAccessory.h"

class Fin : public IAccessory {
public:
  explicit Fin(IBestiole *b);
  ~Fin() override = default;

  void draw(UImg &img) override;
  std::vector<std::string> getAccessories() const override {
    std::vector<std::string> accessories = m_bestiole->getAccessories();
    accessories.push_back("Fin");
    return accessories;
  }
private:
  double m_nu;
};

#endif