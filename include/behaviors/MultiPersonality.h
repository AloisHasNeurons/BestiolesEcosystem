#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include <chrono>
#include <vector>
#include <string>

#include "../interfaces/IBehavior.h"

class IBestiole;

class MultiPersonality : public IBehavior {
 private:
  IBehavior* currentBehavior;
  std::chrono::steady_clock::time_point lastChange =
      std::chrono::steady_clock::now();

 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  MultiPersonality();
  ~MultiPersonality() override;
  MultiPersonality(const MultiPersonality& other) {
    currentBehavior = other.currentBehavior;
  };
  IBehavior* clone() const override { return new MultiPersonality(*this); }
  void changeBehavior();
  std::string getName() const override { return "MultiPersonality"; }
  unsigned char* getColor() const override { return new unsigned char[3]{0, 0, 0}; } // TEMPORARY: MultiPersonality is black
};

#endif  // MULTIPERSONALITY_H