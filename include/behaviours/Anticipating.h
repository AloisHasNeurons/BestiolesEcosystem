#ifndef ANTICIPATING_H
#define ANTICIPATING_H

#include "../interfaces/IBehavior.h"
#include <vector>
class IBestiole;

class Anticipating : public IBehavior {
 private: 
  unsigned char* color = new unsigned char[3]{255, 0, 255}; // Magenta color for Anticipating behavior
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  Anticipating() {}
  Anticipating(const Anticipating& other) { color = other.color; }
  IBehavior* clone() const override {
      return new Anticipating(*this);
  }
  std::string getName() const override { 
      return "Anticipating"; 
  }
};

#endif  // ANTICIPATING_H