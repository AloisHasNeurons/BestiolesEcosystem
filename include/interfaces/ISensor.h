// ISensor.h

#ifndef ISENSOR_H
#define ISENSOR_H

#include "patterns/Decorateur.h"

class ISensor : public Decorator {
 public:
  explicit ISensor(IBestiole* b) : Decorator(b) {}
  ~ISensor() override = default;

  // Sensors must implement these (override Decorator/IBestiole defaults)
  virtual bool canSee(const IBestiole& b) const override = 0;
  virtual void draw(UImg& img) override = 0;
};

#endif  // ISENSOR_H