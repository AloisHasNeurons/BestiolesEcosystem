#include <iostream>

#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"

int main() {
  Aquarium ecosystem(640, 480, 30);

  for (int i = 1; i <= 20; ++i) {
    ecosystem.getEnvironment().addMember(new Bestiole());
  }
  ecosystem.run();

  return 0;
}