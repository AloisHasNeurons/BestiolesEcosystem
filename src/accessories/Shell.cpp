#include "accessories/Shell.h"
#include <cmath> // std::cos, std::sin, M_PI
#include "core/Aquarium.h"

Shell::Shell(IBestiole *b) : IAccessory(b) {
  // Modify Bestiole parameters using multiplicative factors instead of changing
  // speed directly 1) Slow down: speedFactor /= eta  (when eta > 1, it becomes
  // slower)
  double currentSpeedFactor = m_bestiole->getSpeedFactor();
  double r = static_cast<double>(std::rand()) / RAND_MAX;
  m_teta = Aquarium::getAccessoryConfig().tetaMin +
                r * (Aquarium::getAccessoryConfig().tetaMax -
                     Aquarium::getAccessoryConfig().tetaMin);
  m_omega = Aquarium::getAccessoryConfig().omegaMin +
                 r * (Aquarium::getAccessoryConfig().omegaMax -
                      Aquarium::getAccessoryConfig().omegaMin);
  if (m_teta != 0.0) {
    m_bestiole->setSpeedFactor(currentSpeedFactor / m_teta);
  }

  // 2) Increase armor: armorFactor *= omega  (when omega > 1, it becomes more
  // resistant)
  double currentArmorFactor = m_bestiole->getArmorFactor();
  m_bestiole->setArmorFactor(currentArmorFactor * m_omega);
}

Shell::Shell(const Shell &other, IBestiole *inner)
    : IAccessory(inner), m_omega(other.m_omega), m_teta(other.m_teta) {
  // Apply the same modifications to the new inner bestiole
  double currentSpeedFactor = m_bestiole->getSpeedFactor();
  if (m_teta != 0.0) {
    m_bestiole->setSpeedFactor(currentSpeedFactor / m_teta);
  }

  double currentArmorFactor = m_bestiole->getArmorFactor();
  m_bestiole->setArmorFactor(currentArmorFactor * m_omega);
}

void Shell::action(Environment &env, IBestiole *self) {
  m_bestiole->action(env, self ? self : this);
}

void Shell::draw(UImg &img) {
  // Draw a black outline surrounding the body and head
  int cx = getX();
  int cy = getY();
  double theta = getOrientation();
  double size = getSize();

  // Calculate head position (same logic as Bestiole but for outline)
  double headX = cx + std::cos(theta) * size / 2.1;
  double headY = cy - std::sin(theta) * size / 2.1;

  double angleDeg = -theta * 180.0 / M_PI;

  // Outline color: black
  T outlineColor[3] = {0, 0, 0};

  // Draw slightly larger shapes to create the outline effect
  // Body outline
  img.draw_ellipse(cx, cy, size + 3.0, (size / 5.0) + 3.0, angleDeg,
                   outlineColor);
  // Head outline
  img.draw_circle(headX, headY, (size / 2.0) + 3.0, outlineColor);

  Decorator::draw(img);
}

Shell *Shell::clone() {
  return new Shell(*this, m_bestiole->clone());
}