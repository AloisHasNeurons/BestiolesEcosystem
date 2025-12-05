#ifndef EARS_H
#define EARS_H

#include "../interfaces/ISensor.h"
#include "UImg.h"

class Ears : public ISensor {
private:
  double m_delta; // hearing distance δ
  double m_gamma; // detection capability γ

public:
  explicit Ears(IBestiole *b);

  ~Ears() override = default;

  void draw(UImg &img);

  bool canSee(const IBestiole &b) const override;

  virtual IBestiole *clone() override;

  std::string getDescription() const override;

  bool detect(IBestiole &b) override;
};

#endif // EARS_H