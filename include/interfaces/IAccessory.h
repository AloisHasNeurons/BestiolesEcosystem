// IAccessory.h
#ifndef IACCESSORY_H
#define IACCESSORY_H

#include "patterns/Decorateur.h"

class IAccessory : public Decorator {
 public:
  explicit IAccessory(IBestiole* b) : Decorator(b) {}
  ~IAccessory() override = default;
  
  virtual void move(Environment& env) = 0;
  void action(Environment& env) override { move(env); }
  virtual void draw() = 0;
};
#endif  // IACCESSORY_H