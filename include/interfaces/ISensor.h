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
  virtual IBestiole *clone() = 0;
  virtual std::string getDescription() const = 0;
  virtual void draw(UImg &img) = 0;
};
#endif // ISENSOR_H