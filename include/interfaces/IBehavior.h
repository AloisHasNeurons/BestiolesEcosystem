#ifndef IBEHAVIOR_H
#define IBEHAVIOR_H

class IBehavior {
 public:
  virtual ~IBehavior() {}
  virtual double& steer(double orientation) = 0;
};

#endif  // IBEHAVIOR_H