#ifndef EYES_H
#define EYES_H

#include "core/Environment.h"
#include "interfaces/ISensor.h"

class Eyes : public ISensor {
private:
  double m_delta; // seeing distance δ
  double m_alpha; // field-of-view angle (radians)
  double m_gamma; // detection capability γ

public:
  explicit Eyes(IBestiole *b);

  ~Eyes() override = default;

  void draw(UImg &img) override;

  bool canSee(const IBestiole &b) const override;

  virtual IBestiole *clone() override;

  std::string getDescription() const override;

  bool detect(IBestiole &b) override;
};

#endif // EYES_H