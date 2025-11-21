#include "core/Environment.h"

#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "core/Bestiole.h"
#include "patterns/Factory.h"

// Define static members
const unsigned char Environment::white[] = {255, 255, 255};
double Environment::birthRate = 0.1;
double Environment::deltaEyeMin = 0.0;
double Environment::deltaEyeMax = M_PI / 2;
double Environment::alpha = M_PI / 4;
double Environment::gammaEyeMin = 0.0;
double Environment::gammaEyeMMax = 20.0;

Environment::Environment(int _width, int _height, IFactory& f)
    : UImg(_width, _height, 1, 3), factory(f) {
  std::cout << "const Environment" << std::endl;
  std::srand(time(NULL));
}

Environment::Environment(IFactory& f) : factory(f) {
  std::cout << "const Environment" << std::endl;
  std::srand(time(NULL));
}

Environment::~Environment(void) {
  std::cout << "dest Environment" << std::endl;

  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    delete (*it);
  }
  bestiolesList.clear();
  bestiolesToAdd.clear();
}

void Environment::step(void) {
  for (IBestiole* b : bestiolesToAdd) {
    bestiolesList.push_back(b);
  }
  bestiolesToAdd.clear();
  
  cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* b = (*it);

    b->action(*this);
    b->draw(*this);

    for (std::vector<IBestiole*>::iterator it2 = bestiolesList.begin();
         it2 != bestiolesList.end(); ++it2) {
      IBestiole* other = (*it2);

      if (b == other) continue;

      double dx = b->getX() - other->getX();
      double dy = b->getY() - other->getY();
      double dist = std::sqrt(dx * dx + dy * dy);

      double collisionThreshold = 8.0;

      if (dist < collisionThreshold) {
        b->collision();
      }
    }
  }

  double randomValue =
      static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX) + 1.0);

  if (randomValue < birthRate) {
    IBestiole* newBestiole = factory.createBestiole();
    if (newBestiole) {
      this->addMember(newBestiole);
    }
  }
}

void Environment::addMember(IBestiole* b) {
  this->bestiolesToAdd.push_back(b);  // Add bestiole to the list
  b->initCoords(this->width(), this->height());
}

int Environment::neighborCount(const IBestiole& b) {
  int nb = 0;
  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it);

    if (&b == other) continue;

    if (b.canSee(*other)) {
      ++nb;
    }
  }
  return nb;
}

std::vector<double> Environment::getBehaviorDistribution() const {
  std::vector<double> probs;
  for (const auto& pair : behaviorDistribution) {
    probs.push_back(pair.second);
  }
  return probs;
}