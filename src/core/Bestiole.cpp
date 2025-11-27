#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>

#include "core/Environment.h"
#include "interfaces/IBehavior.h"
#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_SPEED = 10.;
const double Bestiole::VIEW_LIMIT = 30.;
const int Bestiole::MAX_LIFE_SPAN = 1000;

int Bestiole::next = 0;

// Constructor without defining behavior
Bestiole::Bestiole(void) {
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

  speedFactor   = 1.0;
  armorFactor   = 1.0;
  camouflagePsi = 0.0;

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

  // Make sure the clone method of IBehavior is implemented
  if (b.behavior) {
    behavior.reset(b.behavior->clone());
  } else {
    behavior = nullptr;
  }
}

// New constructor with behavior
Bestiole::Bestiole(std::unique_ptr<IBehavior> b) 
    : behavior(std::move(b)) // Initialize behavior with the provided unique_ptr
{
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") with behavior" << std::endl;

  x = y = 0;
  cumulativeX = cumulativeY = 0.;
  orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  speed = static_cast<double>(rand()) / RAND_MAX * MAX_SPEED;

  color = new unsigned char[3];
  
  color[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  return;
  } //We should find a way to indicate which behavior is assigned (e.g., via parameters)


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
  double dx = cos(orientation) * speed * speedFactor;
  double dy = -sin(orientation) * speed * speedFactor;
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
    // Need to implement getBestiolesList in Environment
    std::vector<IBestiole*> bestiolesList = myEnvironment.getBestiolesList();
    orientation = this->behavior->steer(*this, bestiolesList);
    speed = this->behavior->speed(*this, bestiolesList) * speedFactor;
  }

  if (speed > MAX_SPEED) {
    speed = MAX_SPEED;
  } else if (speed < 0.) {
    speed = 0.;
  }

  move(myEnvironment.width(), myEnvironment.height());
}

// Modifier cette méthode pour prendre en compte les différents types de bestioles (comportements) et leurs accessoires/capteurs
// yeux : deux petits points
// oreilles : un losange
// nageoire : un triangle
// camouflage : opacité
// carapace : un gros point
// comportement : une couleur = un comportement

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

// Note: This requires 'identity' to be accessible,
// which is true because of the 'friend' declaration in Bestiole.h
bool operator==(const Bestiole& b1, const Bestiole& b2) {
  return (b1.identity == b2.identity);
}


bool Bestiole::canSee(const IBestiole& b) const {
  return false;
}

// Our implementations

IBestiole* Bestiole::clone() {
  return new Bestiole(*this);
}

bool Bestiole::collision(IBestiole* b, IBestiole* other) {
    // Check for collision
    double dist = std::sqrt((b->getX() - other->getX()) * (b->getX() - other->getX()) +
                  (b->getY() - other->getY()) * (b->getY() - other->getY()));

    // If a collision is detected
    if (dist < Bestiole::AFF_SIZE) {

      // Choose a random hazard level between 0 and 1
      double hazard = static_cast<double>(std::rand()) / RAND_MAX;

      // Compare hazard with resistance to determine if the collision is fatal
      // If hazard exceeds resistance, the bestiole dies
      if (hazard > resistance * armorFactor) {
          kill(0);
          return true;
      }

      // Bestiole survives the collision
      return false;
  }

    // No collision
    return false;
}

// Implement kill with delay
void Bestiole::kill(int delay) {
  if (delay <= 0) {
    lifeSpan = -1;
  } else {
    lifeSpan = delay;
  }
}

// Change behavior dynamically
void Bestiole::changeBehavior(std::unique_ptr<IBehavior> behavior) {
  if (!behavior) {
    return;
  }

  this->behavior = std::move(behavior);
  // Implement getName() in IBehavior for the dynamic behavior type retrieval
  this->behaviorString = this->behavior->getName();
}

// Getters
int Bestiole::getX() const { return x; }
int Bestiole::getY() const { return y; }
double Bestiole::getOrientation() const { return orientation; }
double Bestiole::getSpeed() const { return speed; }
double Bestiole::getMaxSpeed() const { return MAX_SPEED; }
double Bestiole::getResistance() const { return resistance; }
double Bestiole::getOpacity() const { return opacity; }
double Bestiole::getSize() const { return AFF_SIZE; }
int Bestiole::getLifeSpan() const { return lifeSpan; }
IBehavior* Bestiole::getBehavior() const { return behavior.get(); }
std::string Bestiole::getBehaviorString() const { return behaviorString; }
double Bestiole::getSpeedFactor() const { return speedFactor; }
double Bestiole::getArmorFactor() const { return armorFactor; }
double Bestiole::getCamouflage() const { return camouflagePsi; }

// Setters for new parameters(Use in Decorator pattern)
void Bestiole::setSpeedFactor(double f) { speedFactor = f; }
void Bestiole::setArmorFactor(double f) { armorFactor = f; }
void Bestiole::setCamouflage(double psi) { camouflagePsi = psi; }