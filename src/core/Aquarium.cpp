#include "core/Aquarium.h"

#include "core/Milieu.h"

Aquarium::Aquarium(int width, int height, int _delay)
    : CImgDisplay(), delay(_delay) {
  int screenWidth = 1280;   // screen_width();
  int screenHeight = 1024;  // screen_height();

  std::cout << "const Aquarium" << std::endl;

  flotte = new Milieu(width, height);
  assign(*flotte, "Simulation d'ecosysteme");

  move(static_cast<int>((screenWidth - width) / 2),
       static_cast<int>((screenHeight - height) / 2));
}

Aquarium::~Aquarium(void) {
  delete flotte;

  std::cout << "dest Aquarium" << std::endl;
}

void Aquarium::run(void) {
  std::cout << "running Aquarium" << std::endl;

  while (!is_closed()) {
    std::cout << "iteration de la simulation" << std::endl;

    if (is_key()) {
      std::cout << "Vous avez presse la touche "
                << static_cast<unsigned char>(key());
      std::cout << " (" << key() << ")" << std::endl;
      if (is_keyESC()) close();
    }

    flotte->step();
    display(*flotte);

    wait(delay);

  }  // while
}
