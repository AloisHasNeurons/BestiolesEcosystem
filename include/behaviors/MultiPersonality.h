#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include "../interfaces/IBehavior.h"

class MultiPersonality : public IBehavior {
 public:
  double& steer(double orientation) override;
  void changeBehavior(IBehavior* newBehavior);
};

#endif  // MULTIPERSONALITY_H