#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"
#include "core/Environment.h"
#include "interfaces/IBehavior.h"

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_SPEED = 10.;
const double Bestiole::VIEW_LIMIT = 30.;
const int Bestiole::MAX_LIFE_SPAN = 1000;

int Bestiole::next = 0;

// Constructor without defining behavior
/*Bestiole::Bestiole(void) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") by default" << std::endl;

  x = y = 0;
  cumulativeX = cumulativeY = 0.;
  orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  speed = static_cast<double>(rand()) / RAND_MAX * MAX_SPEED;
  lifeSpan = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * MAX_LIFE_SPAN);

  color = new unsigned char[3];
  color[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);

  resistance = static_cast<double>(rand()) / RAND_MAX;
  opacity = static_cast<double>(rand()) / RAND_MAX;

  behavior = nullptr;
}*/

Bestiole::Bestiole(std::unique_ptr<IBehavior> b)
    : behavior(std::move(b))
{
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") with behavior" << std::endl;

  x = y = 0;
  cumulativeX = cumulativeY = 0.;
  orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  speed = static_cast<double>(rand()) / RAND_MAX * MAX_SPEED;

  lifeSpan = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * MAX_LIFE_SPAN);
  resistance = static_cast<double>(rand()) / RAND_MAX;
  opacity = static_cast<double>(rand()) / RAND_MAX;

  color = new unsigned char[3];
  color[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
}

// Copy constructor
Bestiole::Bestiole(const Bestiole& b) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") by copy" << std::endl;

  x = b.x;
  y = b.y;
  cumulativeX = cumulativeY = 0.;
  orientation = b.orientation;
  speed = b.speed;
  lifeSpan = b.lifeSpan;
  resistance = b.resistance;
  opacity = b.opacity;

  color = new unsigned char[3];
  memcpy(color, b.color, 3 * sizeof(unsigned char));

  // [Temporary Fix] clone() is not implemented in IBehavior yet.
  // Resetting behavior to nullptr to prevent compilation error.
  behavior = nullptr;
}

Bestiole::~Bestiole(void) {
  delete[] color;

  std::cout << "dest Bestiole" << std::endl;
}

void Bestiole::initCoords(int xLim, int yLim) {
  x = rand() % xLim;
  y = rand() % yLim;
}

void Bestiole::move(int xLim, int yLim) {
  double nx, ny;
  double dx = cos(orientation) * speed;
  double dy = -sin(orientation) * speed;
  int cx, cy;

  cx = static_cast<int>(cumulativeX);
  cumulativeX -= cx;
  cy = static_cast<int>(cumulativeY);
  cumulativeY -= cy;

  nx = x + dx + cx;
  ny = y + dy + cy;

  if ((nx < 0) || (nx > xLim - 1)) {
    orientation = M_PI - orientation;
    cumulativeX = 0.;
  } else {
    x = static_cast<int>(nx);
    cumulativeX += nx - x;
  }

  if ((ny < 0) || (ny > yLim - 1)) {
    orientation = -orientation;
    cumulativeY = 0.;
  } else {
    y = static_cast<int>(ny);
    cumulativeY += ny - y;
  }
}

void Bestiole::action(Environment& myEnvironment) {
  if (lifeSpan > 0) {
    lifeSpan--;
    if (lifeSpan == 0) {
      this->kill(0);
    }
  }

  if (lifeSpan <= 0) {
    return;
  }

  if (behavior) {
    std::vector<IBestiole*> neighbors = myEnvironment.getBestiolesList();
    // Pass the list to the behavior
    orientation = this->behavior->steer(*this, neighbors);
    speed = this->behavior->speed(*this, neighbors);
  }

  if (speed > MAX_SPEED) {
    speed = MAX_SPEED;
  } else if (speed < 0.) {
    speed = 0.;
  }

  move(myEnvironment.width(), myEnvironment.height());
}

void Bestiole::draw(UImg& support) {
  if (lifeSpan < 0) {
    return;
  }

  double xt = x + cos(orientation) * AFF_SIZE / 2.1;
  double yt = y - sin(orientation) * AFF_SIZE / 2.1;

  support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                       -orientation / M_PI * 180., color);
  support.draw_circle(xt, yt, AFF_SIZE / 2., color);
}

bool operator==(const Bestiole& b1, const Bestiole& b2) {
  return (b1.identity == b2.identity);
}

bool Bestiole::canSee(const IBestiole& b) const {
  if (lifeSpan < 0) {
    return false;
  }

  double dist;
  dist = std::sqrt((x - b.getX()) * (x - b.getX()) +
                   (y - b.getY()) * (y - b.getY()));
  return (dist <= VIEW_LIMIT);
}

IBestiole* Bestiole::clone() { return new Bestiole(*this); }

bool Bestiole::collision() {
  double hazard = static_cast<double>(std::rand()) / RAND_MAX;

  if (hazard > resistance) {
    kill(0);
    return true;
  }

  return false;
}

void Bestiole::kill(int delay) {
  if (delay <= 0) {
    lifeSpan = -1;
  } else {
    lifeSpan = delay;
  }
}

void Bestiole::changeBehavior(std::unique_ptr<IBehavior> behavior) {
  if (!behavior) {
    return;
  }

  this->behavior = std::move(behavior);
  // [Fix] getName() is not in IBehavior. Using placeholder.
  this->behaviorString = "Unknown";
}

int Bestiole::getX() const { return x; }
int Bestiole::getY() const { return y; }
double Bestiole::getOrientation() const { return orientation; }
double Bestiole::getSpeed() const { return speed; }
double Bestiole::getMaxSpeed() const { return MAX_SPEED; }
double Bestiole::getResistance() const { return resistance; }
double Bestiole::getOpacity() const { return opacity; }
int Bestiole::getLifeSpan() const { return lifeSpan; }
IBehavior* Bestiole::getBehavior() const { return behavior.get(); }
std::string Bestiole::getBehaviorString() const { return behaviorString; }