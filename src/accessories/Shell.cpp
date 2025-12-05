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
  Decorator::draw(img);

  // Draw an outer “shell” around the body
  int cx = getX();
  int cy = getY();
  double theta = getOrientation();
  double size = getSize();

  // The shell is slightly larger than the body
  double a = size + 2.0;       // major axis
  double b = size / 5.0 + 1.0; // minor axis
  double angleDeg = -theta * 180.0 / M_PI;

  // Shell color: dark gray
  T shellColor[3] = {60, 60, 60};

  img.draw_ellipse(cx, cy, a, b, angleDeg, shellColor, 1.0f);
}

IBestiole *Shell::clone() {
  return new Shell(*this, m_bestiole->clone());
}