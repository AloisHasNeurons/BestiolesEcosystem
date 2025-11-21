#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include "../interfaces/IBehavior.h"
#include <vector>
#include <chrono>
#include <string>

class IBestiole;

class MultiPersonality : public IBehavior {
private:
  unsigned char* color; // the color of the current behavior
  IBehavior* currentBehavior;
  std::chrono::steady_clock::time_point lastChange = std::chrono::steady_clock::now();
public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  MultiPersonality();
  MultiPersonality(const MultiPersonality& other) { currentBehavior = other.currentBehavior; };
  IBehavior* clone() const override {
      return new MultiPersonality(*this);
  }
  void changeBehavior();
  std::string getName() const override { 
      return "MultiPersonality"; 
  }
  unsigned char* getColor() const override {
      return color;
  }
};

#endif  // MULTIPERSONALITY_H