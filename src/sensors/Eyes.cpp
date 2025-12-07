#include "sensors/Eyes.h"
#include <cmath>
#include <cstdlib>
#include "UImg.h"
#include "core/Aquarium.h"
#include "patterns/Decorator.h"

// Utility function: generate a uniform random number in [min, max]
static double uniformDouble(double minVal, double maxVal) {
  double r = static_cast<double>(std::rand()) / RAND_MAX; // [0,1]
  return minVal + r * (maxVal - minVal);
}

Eyes::Eyes(IBestiole *b) : ISensor(b) {
  // Read eye-parameter ranges from the environment configuration
  const SensorConfig &cfg = Aquarium::getEyeConfig();

  // Field-of-view angle α is randomly selected within [alphaMin, alphaMax]
  double alphaDeg = uniformDouble(cfg.alphaMin, cfg.alphaMax);
  m_alpha = alphaDeg * std::acos(-1.0) / 180.0; // convert degrees → radians

  // Seeing distance δ randomly chosen within [deltaMin, deltaMax]
  m_delta = uniformDouble(cfg.deltaMin, cfg.deltaMax);

  // Detection capability γ randomly chosen within [gammaMin, gammaMax]
  m_gamma = uniformDouble(cfg.gammaMin, cfg.gammaMax);
}

Eyes::Eyes(const Eyes &other, IBestiole *inner)
    : ISensor(inner), m_delta(other.m_delta), m_alpha(other.m_alpha),
      m_gamma(other.m_gamma) {}

Eyes *Eyes::clone() {
  return new Eyes(*this, m_bestiole->clone());
}

void Eyes::draw(UImg &img) {
  m_bestiole->draw(img);

  // Draw a small dot in front of the body to represent the “eye”
  int cx = getX();
  int cy = getY();
  double theta = getOrientation(); // radians

  // Eye position: offset from the center in the orientation direction
  double r = m_bestiole->getSize() * 0.4; // use the decorated bestiole's size
  int eyeX = static_cast<int>(cx + std::cos(theta) * r);
  int eyeY = static_cast<int>(cy - std::sin(theta) * r); // y-axis is downward

  unsigned char eyeColor[3] = {255, 255, 255}; // white eye
  img.draw_circle(eyeX, eyeY, 2, eyeColor);
}

bool Eyes::canSee(const IBestiole &b) const {
  // 1) Distance check: must be within [deltaMin, deltaMax]
  double x1 = static_cast<double>(getX());
  double y1 = static_cast<double>(getY());
  double x2 = static_cast<double>(b.getX());
  double y2 = static_cast<double>(b.getY());

  double dx = x2 - x1;
  double dy = y1 - y2; // screen coordinates: y increases downward
  double dist = std::sqrt(dx * dx + dy * dy);

  if (dist > m_delta)
    return false;

  // 2) Field-of-view check: target must lie inside forward sector
  double theta = getOrientation();      // my orientation
  double angleToB = std::atan2(dy, dx); // direction toward the target

  // Normalize angle difference to [-π, π]
  double dTheta =
      std::atan2(std::sin(angleToB - theta), std::cos(angleToB - theta));

  if (std::fabs(dTheta) > m_alpha * 0.5)
    return false;

  // 3) Camouflage check: γ must be greater than ψ to see the target
  double psi = b.getCamouflage(); // camouflage strength of the target
  if (m_gamma <= psi)
    return false;

  return true;
}

bool Eyes::canHear(const IBestiole &b) const {
  // Delegate to the decorated bestiole's canHear method
  return m_bestiole->canHear(b);
}

bool Eyes::detect(IBestiole &b) { return canSee(b); }