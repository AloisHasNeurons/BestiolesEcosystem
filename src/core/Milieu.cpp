#include "core/Milieu.h"

#include <cstdlib>
#include <ctime>

#include "core/Bestiole.h"

const unsigned char Milieu::white[] = {255, 255, 255};

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3) {
  std::cout << "const Milieu" << std::endl;
  std::srand(time(NULL));
}

Milieu::~Milieu(void) {
  std::cout << "dest Milieu" << std::endl;

  for (std::vector<IBestiole*>::iterator it = listeBestioles.begin();
       it != listeBestioles.end(); ++it) {
    delete (*it);
  }
  listeBestioles.clear();
}

void Milieu::step(void) {
  cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);

  for (std::vector<IBestiole*>::iterator it = listeBestioles.begin();
       it != listeBestioles.end(); ++it) {
    IBestiole* b = (*it);

    b->action(*this);
    b->draw(*this);
  }
}

int Milieu::nbVoisins(const IBestiole& b) {
  int nb = 0;
  for (std::vector<IBestiole*>::iterator it = listeBestioles.begin();
       it != listeBestioles.end(); ++it) {
    IBestiole* autre = (*it);  // 'autre' est un pointeur IBestiole*

    // Ne pas se compter soi-même (comparaison d'adresses)
    if (&b == autre) continue;

    // Utiliser la méthode jeTeVois (qui prend une IBestiole&)
    if (b.jeTeVois(*autre)) {
      ++nb;
    }
  }
  return nb;
}