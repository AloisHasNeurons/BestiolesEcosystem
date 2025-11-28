// ISensor.h
#ifndef ISENSOR_H
#define ISENSOR_H

class IBestiole;
#include "patterns/Decorator.h"
class ISensor : public Decorator {
public:
  explicit ISensor(IBestiole *b) : Decorator(b) {}
  virtual ~ISensor() {}
  virtual bool detect(IBestiole &b) = 0;

  virtual void draw(UImg &img) = 0;

  virtual void setCloneRate(double newCloneRate) override {}

  virtual void setOrientation(double o) override {}
};
#endif // ISENSOR_H