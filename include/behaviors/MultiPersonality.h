#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include <chrono>
#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

class IBestiole;

class MultiPersonality : public IBehavior {
 private:
  IBehavior* currentBehavior;
  std::chrono::steady_clock::time_point lastChange;

 public:
  MultiPersonality();
  ~MultiPersonality() override;

  MultiPersonality(const MultiPersonality& other) {
    if (other.currentBehavior) {
      currentBehavior = other.currentBehavior->clone();
    } else {
      currentBehavior = nullptr;
    }
    lastChange = other.lastChange;
  }

  IBehavior* clone() const override { return new MultiPersonality(*this); }

  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  void changeBehavior();

  std::string getName() const override { return "MultiPersonality"; }

  // [Fix] Dynamically retrieve the color from the current active behavior
  unsigned char* getColor() const override {
    return currentBehavior ? currentBehavior->getColor() : nullptr;
  }
};

#endif  // MULTIPERSONALITY_H