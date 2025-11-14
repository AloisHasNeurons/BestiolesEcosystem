#include <iostream>

#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Milieu.h"

int main() {
  Aquarium ecosysteme(640, 480, 30);

  for (int i = 1; i <= 20; ++i) {
    ecosysteme.getMilieu().addMember(new Bestiole());
  }
  ecosysteme.run();

  return 0;
}