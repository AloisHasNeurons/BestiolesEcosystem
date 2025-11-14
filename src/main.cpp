#include <iostream>

#include "Aquarium.h"
#include "Bestiole.h"
#include "Milieu.h"

using namespace std;

int main() {
  Aquarium ecosysteme(640, 480, 30);

  for (int i = 1; i <= 20; ++i) ecosysteme.getMilieu().addMember(Bestiole());
  ecosysteme.run();

  return 0;
}
