#ifndef SHELL_H
#define SHELL_H

#include <string>
#include <vector>

#include "../interfaces/IAccessory.h"

class Shell : public IAccessory {
public:
  explicit Shell(IBestiole *b);
  Shell(const Shell &other, IBestiole *inner);
  ~Shell() override = default;

  Shell *clone() override;

  void action(Environment &env, IBestiole *self = nullptr) override;
  void draw(UImg &img) override;
  std::vector<std::string> getAccessories() const override {
    std::vector<std::string> accessories = m_bestiole->getAccessories();
    accessories.push_back("Shell");
    return accessories;
  }

private:
  double m_omega;
  double m_teta;
};

#endif