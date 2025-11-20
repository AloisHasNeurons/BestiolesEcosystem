#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>

#include "core/Environment.h"
#include "interfaces/IBehavior.h"
#include "behaviours/Anticipating.h"
#include "behaviouers/Fearful.h"
#include "behaviours/Gregarious.h"
#include "behaviours/Kamikaze.h"
#include "behaviours/MultiPersonality.h"

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

// New constructor with environment to set behavior
Bestiole::Bestiole(Environment* env) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") with environment" << std::endl;

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

  if (env) {
    const std::map<std::string, int>& config = env->getBehaviorConfig();
    
    int totalWeight = 0;
        for (const auto& pair : config) totalWeight += pair.second;

        if (totalWeight > 0) {
            int randomVal = std::rand() % totalWeight;
            int currentSum = 0;

            for (const auto& pair : config) {
                currentSum += pair.second;
                if (randomVal < currentSum) {
                    std::string type = pair.first;
                    
                    // Instantiate the appropriate behavior based on the selected type
                    if (type == "Gregarious") {
                        behavior = std::unique_ptr<Gregarious>(new Gregarious());
                    } 
                    else if (type == "Fearful") {
                        behavior = std::unique_ptr<Fearful>(new Fearful());
                    } 
                    else if (type == "Kamikaze") {
                        behavior = std::unique_ptr<Kamikaze>(new Kamikaze());
                    } 
                    else if (type == "Anticipating") {
                        behavior = std::unique_ptr<Anticipating>(new Anticipating());
                    }
                    else if (type == "MultiPersonality") {
                        behavior = std::unique_ptr<MultiPersonality>(new MultiPersonality());
                    }
                    else {
                        std::cerr << "Unknown behavior type: " << type << std::endl;
                        behavior = nullptr;
                    }
                    
                    this->behaviorString = type;
                    break; 
                }
            }
        }

  }
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
    // C'est quoi le double en argument du diriger(double) dans le diagramme uml ?
    orientation = this->behavior->direct();
    speed = this->behavior->speed();
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
  if (lifeSpan < 0) {
    return false;
  }
  
  double dist;
  dist = std::sqrt((x - b.getX()) * (x - b.getX()) +
                   (y - b.getY()) * (y - b.getY()));
  return (dist <= VIEW_LIMIT);
}

// Our implementations

IBestiole* Bestiole::clone() { 
  return new Bestiole(*this); 
}

bool Bestiole::collision() {
    // Choose a random hazard level between 0 and 1
    double hazard = static_cast<double>(std::rand()) / RAND_MAX;

    // Compare hazard with resistance to determine if the collision is fatal 
    // If hazard exceeds resistance, the bestiole dies
    if (hazard > resistance) {
        kill(0); 
        return true; 
    }

    // Bestiole survives the collision
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
int Bestiole::getLifeSpan() const { return lifeSpan; }
IBehavior* Bestiole::getBehavior() const { return behavior.get(); }
std::string Bestiole::getBehaviorString() const { return behaviorString; }