#ifndef EYES_H
#define EYES_H

#include <string>
#include <vector>

#include "core/Environment.h"
#include "interfaces/ISensor.h"

class Eyes : public ISensor {
private:
  double m_delta; // seeing distance δ
  double m_alpha; // field-of-view angle (radians)
  double m_gamma; // detection capability γ

public:
  explicit Eyes(IBestiole *b);
  Eyes(const Eyes &other, IBestiole *inner);

  ~Eyes() override = default;

  IBestiole *clone() override;

  void draw(UImg &img) override;
  std::vector<std::string> getSensors() const override {
    std::vector<std::string> sensors = m_bestiole->getSensors();
    sensors.push_back("Eyes");
    return sensors;
  }

  bool canSee(const IBestiole &b) const override;

  bool detect(IBestiole &b) override;

  void setCloneRate(double newCloneRate) override {}

  void setOrientation(double o) override {}
};

#endif // EYES_H