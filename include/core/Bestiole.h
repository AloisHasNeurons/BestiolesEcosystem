#ifndef BESTIOLE_H
#define BESTIOLE_H

#include <memory>
#include <utility>
#include <string>

#include "../interfaces/IBestiole.h"
#include "UImg.h"

class Environment;
class IBehavior;

class Bestiole : public IBestiole {
 private:
  static const double AFF_SIZE;
  static const double MAX_SPEED;
  static const double VIEW_LIMIT;
  static const int MAX_LIFE_SPAN;
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

  std::string behaviorString;

  std::unique_ptr<IBehavior> behavior;

 private:
  void move(int xLim, int yLim);

 public:
  Bestiole(void);
  Bestiole(const Bestiole& b);
  Bestiole(std::unique_ptr<IBehavior> b); // Constructor with behavior (added by Lucie for Factory pattern)
  Bestiole(Environment* env);
  ~Bestiole(void);

  void action(Environment& myEnvironment) override;
  void draw(UImg& support) override;
  void initCoords(int xLim, int yLim) override;

  IBestiole* clone() override;
  bool collision(IBestiole* b, IBestiole* other) override;
  void kill(int delay) override;
  void changeBehavior(std::unique_ptr<IBehavior> behavior) override;

  int getX() const override;
  int getY() const override;
  double getOrientation() const override;
  double getSpeed() const override;
  double getMaxSpeed() const override;
  double getResistance() const override;
  double getOpacity() const override;
  double getSize() const override;
  int getLifeSpan() const override;
  IBehavior* getBehavior() const override;
  std::string getBehaviorString() const override;

  bool canSee(const IBestiole& b) const override;

  friend bool operator==(const Bestiole& b1, const Bestiole& b2);
};

#endif