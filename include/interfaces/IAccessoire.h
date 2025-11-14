// IAccessoire.h
#ifndef IACCESSOIRE_H
#define IACCESSOIRE_H

class IAccessoire {
 public:
  virtual ~IAccessoire() {}
  virtual void changeParam() = 0;
  virtual void draw() = 0;
};
#endif  // IACCESSOIRE_H