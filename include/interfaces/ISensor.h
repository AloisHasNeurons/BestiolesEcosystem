// ISensor.h
#ifndef ISENSOR_H
#define ISENSOR_H

class IBestiole;

class ISensor {
 public:
  virtual ~ISensor() {}
  virtual bool Detect(IBestiole& b) = 0;
  virtual void draw() = 0;
};
#endif  // ISENSOR_H