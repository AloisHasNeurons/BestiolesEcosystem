#ifndef AQUARIUM_H_
#define AQUARIUM_H_

#include <CImg.h>

#include <iostream>

#include "core/Environment.h"

class Aquarium : public cimg_library::CImgDisplay {
 private:
  Environment* population;
  int delay;

 public:
  Aquarium(int width, int height, int _delay);
  ~Aquarium(void);

  Environment& getEnvironment(void) { return *population; }
  void run(void);
};

#endif