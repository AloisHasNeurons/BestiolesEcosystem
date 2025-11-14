#ifndef AQUARIUM_H_
#define AQUARIUM_H_

#include <CImg.h>

#include <iostream>

#include "core/Milieu.h"

class Aquarium : public cimg_library::CImgDisplay {
 private:
  Milieu* flotte;
  int delay;

 public:
  Aquarium(int width, int height, int _delay);
  ~Aquarium(void);

  Milieu& getMilieu(void) { return *flotte; }
  void run(void);
};

#endif