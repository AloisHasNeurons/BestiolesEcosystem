#ifndef IBEHAVIOR_H
#define IBEHAVIOR_H

#include <vector>
#include <string>
class IBestiole;

class IBehavior {
 public:
  virtual ~IBehavior() {}
  virtual double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) = 0;
  virtual double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) = 0;
  virtual IBehavior* clone() const = 0;
  virtual std::string getName() const = 0;
};

#endif  // IBEHAVIOR_H