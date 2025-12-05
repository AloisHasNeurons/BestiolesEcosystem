#include "accessories/Shell.h"
#include <cmath> // std::cos, std::sin, M_PI
#include "core/Aquarium.h"

std::string Shell::getDescription() const {
    return "Shell + " + m_bestiole->getDescription();
}

IBestiole* Shell::clone() {
    return new Shell(m_bestiole->clone());
}

Shell::Shell(IBestiole *b) : IAccessory(b) {
  // Modify Bestiole parameters using multiplicative factors instead of changing
  // speed directly 1) Slow down: speedFactor /= eta  (when eta > 1, it becomes
  // slower)
  double currentSpeedFactor = m_bestiole->getSpeedFactor();
  double r = static_cast<double>(std::rand()) / RAND_MAX;
  double m_teta = Aquarium::getAccessoryConfig().tetaMin +
                r * (Aquarium::getAccessoryConfig().tetaMax -
                     Aquarium::getAccessoryConfig().tetaMin);
  double m_omega = Aquarium::getAccessoryConfig().omegaMin +
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

void Shell::action(Environment &env, IBestiole* self = nullptr) {
  m_bestiole->action(env, self);
}

void Shell::draw(UImg &img) {
  // Draw the shell first, so it appears as a background layer for the body.
  // This prevents the shell from covering the bestiole's head and other accessories.
  int cx = getX();
  int cy = getY();
  double theta = getOrientation();
  double size = getSize();

  // The shell is drawn slightly larger than the base body.
  const double shellMajorAxis = size + 2.0;
  const double shellMinorAxis = size / 5.0 + 2.0; // Made slightly thicker for better visibility
  double angleDeg = -theta * 180.0 / M_PI;

  // Shell color: dark gray
  T shellColor[3] = {60, 60, 60};

  img.draw_ellipse(cx, cy, shellMajorAxis, shellMinorAxis, angleDeg, shellColor, 1.0f);

  // Now, draw the rest of the bestiole (body, head, other accessories) on top of the shell.
  Decorator::draw(img);
}