#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <iostream>

#include "CImg.h"

using namespace cimg_library;

class Environment;
class Factory;

class Aquarium : public CImgDisplay {
 private:
  Environment* population;
  Factory* factory;
  int delay;

 public:
  Aquarium(int width, int height, int _delay);
  ~Aquarium();

  Environment& getEnvironment() { return *population; }

  void run();
};

#endif