#ifndef FIN_H
#define FIN_H

#include "../interfaces/IAccessory.h"

class Fin : public IAccessory {
public:
  explicit Fin(IBestiole *b);
  ~Fin() override = default;

  void action(Environment &env, IBestiole* self) override;
  void draw(UImg &img) override;
  std::string getDescription() const override;
  virtual IBestiole *clone() override;

private:
  double m_nu;
};

#endif