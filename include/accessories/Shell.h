#ifndef SHELL_H
#define SHELL_H

#include "../interfaces/IAccessory.h"

class Shell : public IAccessory {
public:
  explicit Shell(IBestiole *b);
  ~Shell() override = default;

  void action(Environment &env) override;
  void draw(UImg &img) override;

private:
  double m_omega;
  double m_teta;
};

#endif