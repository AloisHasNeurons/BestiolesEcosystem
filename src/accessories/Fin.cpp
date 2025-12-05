#include "accessories/Fin.h"
#include <cmath>  // std::cos, std::sin
#include <random>
#include "core/Aquarium.h"


std::string Fin::getDescription() const {
    return "Fin + " + m_bestiole->getDescription();
}

IBestiole* Fin::clone() {
    return new Fin(m_bestiole->clone());
}

Fin::Fin(IBestiole* b)
    : IAccessory(b) {

  double currentFactor = m_bestiole->getSpeedFactor();

  // Generate a random speed gain coefficient m_nu
  double r = static_cast<double>(std::rand()) / RAND_MAX;
  m_nu = Aquarium::getAccessoryConfig().nuMin +
         r * (Aquarium::getAccessoryConfig().nuMax -
              Aquarium::getAccessoryConfig().nuMin);

  // Apply speed amplification (Decorator modifies the wrapped object's speed)
  m_bestiole->setSpeedFactor(currentFactor * (1.0 + m_nu));
}

void Fin::action(Environment& env, IBestiole* self) {
  // Delegates the action to the wrapped Bestiole.
  // Passing “self” ensures correct cloning of decorated Bestioles.
  m_bestiole->action(env, self);
}

void Fin::draw(UImg& img) {
  // 1. Draw the wrapped Bestiole first (its body)
  Decorator::draw(img);

  // 2. Retrieve Bestiole position and orientation
  int cx = getX();                // Center X
  int cy = getY();                // Center Y
  double orientation = getOrientation(); // Heading (radians)
  double size = getSize();        // Body size (radius)

  // 3. Fin color (deep blue)
  unsigned char finColor[3] = {0, 60, 255};

  // 4. Precompute trigonometric values
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
