#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "core/Milieu.h"
#include "interfaces/IComportement.h"

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_VITESSE = 10.;
const double Bestiole::LIMITE_VUE = 30.;

int Bestiole::next = 0;

Bestiole::Bestiole(void) {
  identite = ++next;

  std::cout << "const Bestiole (" << identite << ") par defaut" << std::endl;

  x = y = 0;
  cumulX = cumulY = 0.;
  orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  vitesse = static_cast<double>(rand()) / RAND_MAX * MAX_VITESSE;

  couleur = new unsigned char[3];
  couleur[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  couleur[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  couleur[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
}

Bestiole::Bestiole(const Bestiole& b) {
  identite = ++next;

  std::cout << "const Bestiole (" << identite << ") par copie" << std::endl;

  x = b.x;
  y = b.y;
  cumulX = cumulY = 0.;
  orientation = b.orientation;
  vitesse = b.vitesse;

  // CORRECTION: 'T' n'est pas défini
  couleur = new unsigned char[3];
  memcpy(couleur, b.couleur, 3 * sizeof(unsigned char));
}

Bestiole::~Bestiole(void) {
  delete[] couleur;

  std::cout << "dest Bestiole" << std::endl;
}

void Bestiole::initCoords(int xLim, int yLim) {
  x = rand() % xLim;
  y = rand() % yLim;
}

void Bestiole::bouge(int xLim, int yLim) {
  double nx, ny;
  double dx = cos(orientation) * vitesse;
  double dy = -sin(orientation) * vitesse;
  int cx, cy;

  cx = static_cast<int>(cumulX);
  cumulX -= cx;
  cy = static_cast<int>(cumulY);
  cumulY -= cy;

  nx = x + dx + cx;
  ny = y + dy + cy;

  if ((nx < 0) || (nx > xLim - 1)) {
    orientation = M_PI - orientation;
    cumulX = 0.;
  } else {
    x = static_cast<int>(nx);
    cumulX += nx - x;
  }

  if ((ny < 0) || (ny > yLim - 1)) {
    orientation = -orientation;
    cumulY = 0.;
  } else {
    y = static_cast<int>(ny);
    cumulY += ny - y;
  }
}

void Bestiole::action(Milieu& monMilieu) {
  bouge(monMilieu.width(), monMilieu.height());
}

void Bestiole::draw(UImg& support) {
  double xt = x + cos(orientation) * AFF_SIZE / 2.1;
  double yt = y - sin(orientation) * AFF_SIZE / 2.1;

  support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                       -orientation / M_PI * 180., couleur);
  support.draw_circle(xt, yt, AFF_SIZE / 2., couleur);
}

bool operator==(const Bestiole& b1, const Bestiole& b2) {
  return (b1.identite == b2.identite);
}

bool Bestiole::jeTeVois(const IBestiole& b) const {
  double dist;
  dist = std::sqrt((x - b.getX()) * (x - b.getX()) +
                   (y - b.getY()) * (y - b.getY()));
  return (dist <= LIMITE_VUE);
}

IBestiole* Bestiole::clone() { return new Bestiole(*this); }

bool Bestiole::collision() { return false; }

void Bestiole::kill(int delay) { this->dureeVie = 0; }

int Bestiole::getX() const { return x; }
int Bestiole::getY() const { return y; }