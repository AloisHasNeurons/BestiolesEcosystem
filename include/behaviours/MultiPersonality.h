#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include "../interfaces/IBehavior.h"
#include <vector>
#include <chrono>

class IBestiole;

class MultiPersonality : public IBehavior {
private:
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
  std::string getName() const { 
      return "MultiPersonality"; 
  }
};

#endif  // MULTIPERSONALITY_H