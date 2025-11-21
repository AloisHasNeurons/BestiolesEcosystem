#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include <chrono>
#include <vector>

#include "../interfaces/IBehavior.h"

class IBestiole;

class MultiPersonality : public IBehavior {
 private:
  IBehavior* currentBehavior;
  std::chrono::steady_clock::time_point lastChange =
      std::chrono::steady_clock::now();

 public:
  MultiPersonality();
  ~MultiPersonality() override;

  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  void changeBehavior();
};

#endif  // MULTIPERSONALITY_H