#include "core/Environment.h"

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "core/Bestiole.h"

const unsigned char Environment::white[] = {255, 255, 255};

Environment::Environment(int _width, int _height)
    : UImg(_width, _height, 1, 3) {
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

    b->action(*this);
    b->draw(*this);
  }
}

int Environment::neighborCount(const IBestiole& b) {
  int nb = 0;
  for (std::vector<IBestiole*>::iterator it = bestiolesList.begin();
       it != bestiolesList.end(); ++it) {
    IBestiole* other = (*it);

    // Do not count oneself (address comparison)
    if (&b == other) continue;

    if (b.canSee(*other)) {
      ++nb;
    }
  }
  return nb;
}