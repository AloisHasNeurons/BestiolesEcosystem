#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include "../interfaces/IBehavior.h"
#include <vector>
class IBestiole;

class MultiPersonality : public IBehavior {
 public:
  double& steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  void changeBehavior(IBehavior* newBehavior);
};

#endif  // MULTIPERSONALITY_H