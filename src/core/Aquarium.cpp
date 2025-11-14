#include "core/Aquarium.h"

#include <iostream>
#include <utility>

#include "core/Environment.h"

Aquarium::Aquarium(int width, int height, int _delay)
    : CImgDisplay(), delay(_delay) {
  int screenWidth = 1280;   // screen_width();
  int screenHeight = 1024;  // screen_height();

  std::cout << "const Aquarium" << std::endl;

  population = new Environment(width, height);
  assign(*population, "Ecosystem Simulation");

  move(static_cast<int>((screenWidth - width) / 2),
       static_cast<int>((screenHeight - height) / 2));
}

Aquarium::~Aquarium(void) {
  delete population;

  std::cout << "dest Aquarium" << std::endl;
}

void Aquarium::run(void) {
  std::cout << "running Aquarium" << std::endl;

  while (!is_closed()) {
    std::cout << "simulation iteration" << std::endl;

    if (is_key()) {
      std::cout << "You pressed key " << static_cast<unsigned char>(key());
      std::cout << " (" << key() << ")" << std::endl;
      if (is_keyESC()) close();
    }

    population->step();
    display(*population);

    wait(delay);

  }  // while
}