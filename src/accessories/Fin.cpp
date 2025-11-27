#include "Fin.h"

#include <cmath>  // std::cos, std::sin

Fin::Fin(IBestiole* b, double _nu)
    : IAccessory(b), nu(_nu) {
  // Use a multiplicative factor to increase speed instead of modifying speed directly
  double currentFactor = m_bestiole->getSpeedFactor();
  m_bestiole->setSpeedFactor(currentFactor * nu);
}

void Fin::action(Environment& env) {
  m_bestiole->action(env);
}

void Fin::draw(UImg& img) {

  IAccessory::draw(img);

  // Draw two small fins behind the body
  int cx = getX();
  int cy = getY();
  double theta = getOrientation();
  double size = getSize();

  // Direction behind the body (opposite orientation)
  double backTheta = theta + M_PI;
  double r = size * 0.6;

  int baseX = static_cast<int>(cx + std::cos(backTheta) * r);
  int baseY = static_cast<int>(cy - std::sin(backTheta) * r);

  // Slight lateral offsets to form left and right fins
  int finLX = baseX + 3;
  int finLY = baseY;
  int finRX = baseX - 3;
  int finRY = baseY;

  // Fin color: blue
  T finColor[3] = {0, 0, 255};

  // Left fin (triangle)
  img.draw_triangle(baseX, baseY,
                    finLX, finLY - 4,
                    finLX, finLY + 4,
                    finColor);

  // Right fin (triangle)
  img.draw_triangle(baseX, baseY,
                    finRX, finRY - 4,
                    finRX, finRY + 4,
                    finColor);
}
