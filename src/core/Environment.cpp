#include "core/Environment.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

#include "core/Bestiole.h"
#include "patterns/Factory.h"

const unsigned char Environment::white[] = {255, 255, 255};

Environment::Environment(int _width, int _height, IFactory& f) : factory(f), UImg(_width, _height, 1, 3) { // factory must be initialized in initializer list
  std::cout << "const Environment" << std::endl;
  std::srand(time(NULL));
}

Environment::Environment (IFactory& f) : factory(f) { // factory must be initialized in initializer list
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
}

void Environment::step(void) {
  cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* b = (*it);

    // Each bestiole acts and is drawn
    b->action(*this);
    b->draw(*this);

    for (std::vector<IBestiole*>::iterator it2 = bestiolesList.begin(); 
         it2 != bestiolesList.end(); ++it2) { // Check for collisions with other bestioles
        IBestiole* other = (*it2);

        // Do not check collision with oneself
        if (b == other) continue;

        // Check for collision & kills if collision occurs
        b->collision(other, b);
        // other->collision(); if there are other types of bestioles that can also die upon collision
    }
  }
  // Randomly add new bestioles based on birth rate
  double randomValue = static_cast<double>(std::rand()) / (static_cast<double>(RAND_MAX) + 1.0); // Random value [0,1)
  if (randomValue < birthRate) {
    // Use a factory to create a new bestiole (allows different concrete types)
    IBestiole* newBestiole = factory.createBestiole();
    this->addMember(newBestiole); // Add it to the environment
  }
}

void Environment::addMember(IBestiole* b) {
    this->bestiolesList.push_back(b); // Add bestiole to the list
    b->initCoords(this->width(), this->height());
  }

int Environment::neighborCount(const IBestiole& b) {
  int nb = 0;
  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin(); // Iterate through bestioles list to count neighbors
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it); // Get pointer to other bestiole

    // Do not count oneself (address comparison)
    if (&b == other) continue;

    if (b.canSee(*other)) {
      ++nb;
    }
  }
  return nb;
}

std::vector<double> Environment::getBehaviorDistribution() const { 
    std::vector<double> probs; // Vector to hold probabilities
    for (const auto& pair : behaviorDistribution) { // Iterate through the map
      probs.push_back(pair.second); // Add probability to vector
    }
    return probs;
  }

