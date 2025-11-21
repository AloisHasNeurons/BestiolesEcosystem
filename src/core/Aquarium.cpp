#include "core/Aquarium.h"

#include <iostream>

#include "core/Environment.h"
#include "patterns/Factory.h"

Aquarium::Aquarium(int width, int height, int _delay)
    : CImgDisplay(), delay(_delay) {
  int screenWidth = 1280;
  int screenHeight = 1024;

  std::cout << "const Aquarium" << std::endl;

  factory = new Factory();
  population = new Environment(width, height, *factory);
  factory->setEnvironment(population);

  assign(*population, "Ecosystem Simulation");
  move(static_cast<int>((screenWidth - width) / 2),
       static_cast<int>((screenHeight - height) / 2));
}

Aquarium::~Aquarium(void) {
  delete population;
  delete factory;

  std::cout << "dest Aquarium" << std::endl;
}

void Aquarium::run(void) {
  std::cout << "running Aquarium" << std::endl;

  while (!is_closed()) {
    if (is_key()) {
      std::cout << "You pressed key " << static_cast<unsigned char>(key())
                << " (" << key() << ")" << std::endl;
      if (is_keyESC()) close();
    }

    population->step();
    display(*population);
    wait(delay);
  }
}