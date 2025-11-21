#ifndef IBESTIOLE_H
#define IBESTIOLE_H

#include <memory>

#include "IsKillable.h"
#include "UImg.h"

class Environment;
class IBehavior;

class IBestiole : public IsKillable {
 public:
  virtual ~IBestiole() {}

  virtual void action(Environment& environment) = 0;
  virtual void draw(UImg& img) = 0;
  virtual void initCoords(int x, int y) = 0;
  virtual IBestiole* clone() = 0;
  virtual bool collision() = 0;
  virtual bool canSee(const IBestiole& b) const = 0;

  virtual void kill(int delay) override = 0;
  virtual void changeBehavior(std::unique_ptr<IBehavior> behavior) = 0;

  virtual int getX() const = 0;
  virtual int getY() const = 0;
  virtual double getOrientation() const = 0;
  virtual double getSpeed() const = 0;
  virtual double getMaxSpeed() const = 0;
  virtual int getLifeSpan() const = 0;
  virtual double getResistance() const = 0;
  virtual double getOpacity() const = 0;
  virtual IBehavior* getBehavior() const = 0;
  virtual std::string getBehaviorString() const = 0;
};

#endif  // IBESTIOLE_H