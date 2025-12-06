#include "accessories/Fin.h"
#include <cmath>  // std::cos, std::sin
#include <random>
#include <utility> // std::pair
#include "core/Aquarium.h"

Fin::Fin(IBestiole* b)
    : IAccessory(b) {
  // Use a multiplicative factor to increase speed instead of modifying speed
  // directly
  double currentFactor = m_bestiole->getSpeedFactor();
  double r = static_cast<double>(std::rand()) / RAND_MAX;
  m_nu = Aquarium::getAccessoryConfig().nuMin +
         r * (Aquarium::getAccessoryConfig().nuMax -
              Aquarium::getAccessoryConfig().nuMin);
  m_bestiole->setSpeedFactor(currentFactor * (1.0 + m_nu));
}

Fin::Fin(const Fin &other, IBestiole *inner)
    : IAccessory(inner), m_nu(other.m_nu) {
  // Apply the same speed modification to the new inner bestiole
  double currentFactor = m_bestiole->getSpeedFactor();
  m_bestiole->setSpeedFactor(currentFactor * (1.0 + m_nu));
}

Fin *Fin::clone() {
  return new Fin(*this, m_bestiole->clone());
}

void Fin::action(Environment& env, IBestiole *self) {
  m_bestiole->action(env, self ? self : this);
}

void Fin::draw(UImg& img) {

  Decorator::draw(img);

  // Draw two small fins behind the body
  int cx = getX();
  int cy = getY();
  double orientation = getOrientation();
  double size = getSize();

  // Fin color: blue
  T finColor[3] = {0, 0, 255};

  // Bestioles use: dx = cos(theta), dy = -sin(theta)
  double cosTheta = std::cos(orientation);
  double sinTheta = std::sin(orientation);

  // Helper lambda: compute rotated coordinates relative to the Bestiole center.
  // u : displacement forward/backward (along the heading)
  // v : displacement sideways (left/right)
  auto getRotatedPoint = [&](double u, double v) -> std::pair<int, int> {
      // Transformation into world coordinates (screen Y grows downward)
      int px = static_cast<int>(cx + u * cosTheta - v * sinTheta);
      int py = static_cast<int>(cy - (u * sinTheta + v * cosTheta));
      return {px, py};
  };

  // --- LEFT FIN ---
  // A triangular fin extending backward and outward from the left side
  auto p1 = getRotatedPoint(0, size * 0.5);          // Front attachment point
  auto p2 = getRotatedPoint(-size * 0.8, size * 1.5); // Fin tip
  auto p3 = getRotatedPoint(-size * 0.5, size * 0.5); // Rear attachment point

  img.draw_triangle(p1.first, p1.second,
                    p2.first, p2.second,
                    p3.first, p3.second,
                    finColor);

  // --- RIGHT FIN ---
  // Symmetric to the left fin (side offset is negated)
  auto p4 = getRotatedPoint(0, -size * 0.5);
  auto p5 = getRotatedPoint(-size * 0.8, -size * 1.5);
  auto p6 = getRotatedPoint(-size * 0.5, -size * 0.5);

  img.draw_triangle(p4.first, p4.second,
                    p5.first, p5.second,
                    p6.first, p6.second,
                    finColor);
}