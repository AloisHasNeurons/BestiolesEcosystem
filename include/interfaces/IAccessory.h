// IAccessory.h
#ifndef IACCESSORY_H
#define IACCESSORY_H

#include "patterns/Decorator.h"

class IAccessory : public Decorator {
public:
  explicit IAccessory(IBestiole *b) : Decorator(b) {}

  ~IAccessory() override = default;

  void action(Environment &env, IBestiole *self = nullptr) override = 0;

  virtual void draw(UImg &img) override = 0;
};
#endif // IACCESSORY_H