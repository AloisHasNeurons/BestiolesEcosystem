#ifndef BESTIOLE_H
#define BESTIOLE_H

#include <memory>
#include <utility>

#include "../interfaces/IBestiole.h"
#include "UImg.h"

class Environment;
class IBehavior;

class Bestiole : public IBestiole {
 private:
  static const double AFF_SIZE;
  static const double MAX_SPEED;
  static const double VIEW_LIMIT;
  static int next;

 private:
  int identity;
  int x, y;
  double cumulativeX, cumulativeY;
  double orientation;
  double speed;

  unsigned char* color;

  double resistance;
  double opacity;
  int lifeSpan;

  std::unique_ptr<IBehavior> behavior;

 private:
  void move(int xLim, int yLim);

 public:
  Bestiole(void);
  Bestiole(const Bestiole& b);
  Bestiole(std::unique_ptr<IBehavior> b); // Constructor with behavior (added by Lucie for Factory pattern)
  ~Bestiole(void);

  void action(Environment& myEnvironment) override;
  void draw(UImg& support) override;
  void initCoords(int xLim, int yLim) override;

  IBestiole* clone() override;
  bool collision() override;
  void kill(int delay) override;

  int getX() const override;
  int getY() const override;
  double getOrientation() const override;
  double getSpeed() const override;
  double getMaxSpeed() const override;
  std::unique_ptr<IBehavior> getBehavior() const;

  bool canSee(const IBestiole& b) const override;

  friend bool operator==(const Bestiole& b1, const Bestiole& b2);
};

#endif