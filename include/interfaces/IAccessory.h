// IAccessory.h
#ifndef IACCESSORY_H
#define IACCESSORY_H

class IAccessory {
 public:
  virtual ~IAccessory() {}
  virtual void updateParameters() = 0;
  virtual void draw() = 0;
};
#endif  // IACCESSORY_H