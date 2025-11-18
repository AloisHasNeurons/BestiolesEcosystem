#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>

#include "core/Environment.h"
#include "interfaces/IBehavior.h"

const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_SPEED = 10.;
const double Bestiole::VIEW_LIMIT = 30.;

int Bestiole::next = 0;

Bestiole::Bestiole(void) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") by default" << std::endl;

  x = y = 0;
  cumulativeX = cumulativeY = 0.;
  orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  speed = static_cast<double>(rand()) / RAND_MAX * MAX_SPEED;

  color = new unsigned char[3];
  color[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  color[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
}

Bestiole::Bestiole(const Bestiole& b) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") by copy" << std::endl;

  x = b.x;
  y = b.y;
  cumulativeX = cumulativeY = 0.;
  orientation = b.orientation;
  speed = b.speed;

  color = new unsigned char[3];
  memcpy(color, b.color, 3 * sizeof(unsigned char));
}

Bestiole::~Bestiole(void) {
  delete[] color;

  std::cout << "dest Bestiole" << std::endl;
}

void Bestiole::initCoords(int xLim, int yLim) {
  x = rand() % xLim;
  y = rand() % yLim;
}

void Bestiole::move(int xLim, int yLim) {
  double nx, ny;
  double dx = cos(orientation) * speed;
  double dy = -sin(orientation) * speed;
  int cx, cy;

  cx = static_cast<int>(cumulativeX);
  cumulativeX -= cx;
  cy = static_cast<int>(cumulativeY);
  cumulativeY -= cy;

  nx = x + dx + cx;
  ny = y + dy + cy;

  if ((nx < 0) || (nx > xLim - 1)) {
    orientation = M_PI - orientation;
    cumulativeX = 0.;
  } else {
    x = static_cast<int>(nx);
    cumulativeX += nx - x;
  }

  if ((ny < 0) || (ny > yLim - 1)) {
    orientation = -orientation;
    cumulativeY = 0.;
  } else {
    y = static_cast<int>(ny);
    cumulativeY += ny - y;
  }
}

void Bestiole::action(Environment& myEnvironment) {
  move(myEnvironment.width(), myEnvironment.height());
}

void Bestiole::draw(UImg& support) {
  double xt = x + cos(orientation) * AFF_SIZE / 2.1;
  double yt = y - sin(orientation) * AFF_SIZE / 2.1;

  support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                       -orientation / M_PI * 180., color);
  support.draw_circle(xt, yt, AFF_SIZE / 2., color);
}

// Note: This requires 'identity' to be accessible,
// which is true because of the 'friend' declaration in Bestiole.h
bool operator==(const Bestiole& b1, const Bestiole& b2) {
  return (b1.identity == b2.identity);
}

bool Bestiole::canSee(const IBestiole& b) const {
  double dist;
  dist = std::sqrt((x - b.getX()) * (x - b.getX()) +
                   (y - b.getY()) * (y - b.getY()));
  return (dist <= VIEW_LIMIT);
}

IBestiole* Bestiole::clone() { return new Bestiole(*this); }

bool Bestiole::collision() { return false; }

void Bestiole::kill(int delay) { this->lifeSpan = 0; }

int Bestiole::getX() const { return x; }
int Bestiole::getY() const { return y; }
double Bestiole::getOrientation() const { return orientation; }