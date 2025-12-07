#ifndef EARS_H
#define EARS_H

#include <string>
#include <vector>

#include "../interfaces/ISensor.h"
#include "UImg.h"

class Ears : public ISensor {
private:
  double m_delta; // hearing distance δ
  double m_gamma; // detection capability γ

public:
  explicit Ears(IBestiole *b);
  Ears(const Ears &other, IBestiole *inner);

  ~Ears() override = default;

  Ears *clone() override;

  void draw(UImg &img) override;
  std::vector<std::string> getSensors() const override {
    std::vector<std::string> sensors = m_bestiole->getSensors();
    sensors.push_back("Ears");
    return sensors;
  }

  bool canSee(const IBestiole &b) const override;
  bool canHear(const IBestiole &b) const override;

  bool detect(IBestiole &b) override;
};

#endif // EARS_H