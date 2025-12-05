#include "sensors/Ears.h"
#include <cmath>
#include <cstdlib>
#include "UImg.h"
#include "core/Aquarium.h"
#include "patterns/Decorator.h"

// Utility function: generate a uniform random number in [minVal, maxVal]
static double uniformDouble(double minVal, double maxVal) {
  double r = static_cast<double>(std::rand()) / RAND_MAX; // [0,1]
  return minVal + r * (maxVal - minVal);
}

Ears::Ears(IBestiole *b) : ISensor(b) {
  // Read ear configuration from the environment
  const SensorConfig &cfg = Aquarium::getEarConfig();

  // γ is randomly chosen within [gammaMin, gammaMax]
  m_gamma = uniformDouble(cfg.gammaMin, cfg.gammaMax);
  // delta is randomly chosen within [deltaMin, deltaMax]
  m_delta = uniformDouble(cfg.deltaMin, cfg.deltaMax);
}

void Ears::draw(UImg &img) {
  // First draw the underlying bestiole (and other decorators)
  m_bestiole->draw(img);

  // Then draw two small “ears” on both sides of the body
  int cx = getX();
  int cy = getY();
  double theta = getOrientation(); // orientation (radians)

  // Offset distance of ears from the center
  double r = getSize() * 0.5;

  // Positions are computed using orientation ± 90°
  double thetaLeft = theta + M_PI_2;
  double thetaRight = theta - M_PI_2;

  int earLX = static_cast<int>(cx + std::cos(thetaLeft) * r);
  int earLY = static_cast<int>(cy - std::sin(thetaLeft) * r);
  int earRX = static_cast<int>(cx + std::cos(thetaRight) * r);
  int earRY = static_cast<int>(cy - std::sin(thetaRight) * r);

  // Ear color: same as body or fixed color
  T earColor[3] = {0, 0, 0}; // small black ears
  img.draw_circle(earLX, earLY, 2, earColor);
  img.draw_circle(earRX, earRY, 2, earColor);
}

IBestiole *Ears::clone() {
  // Wrap the inner clone with a new Ears decorator
  return new Ears(m_bestiole->clone());
}

std::string Ears::getDescription() const {
  // Add "Ears" to the description chain
  return "Ears + " + m_bestiole->getDescription();
}

bool Ears::canSee(const IBestiole &b) const {
  // Check if this specific sensor (Ears) can detect the target.
  bool canThisSensorHear = false;
  {
    // 1) Distance check: must be within hearing distance m_delta.
    double x1 = static_cast<double>(getX());
    double y1 = static_cast<double>(getY());
    double x2 = static_cast<double>(b.getX());
    double y2 = static_cast<double>(b.getY());
    double dx = x2 - x1;
    double dy = y1 - y2; // Screen coordinates: y increases downward
    double dist = std::sqrt(dx * dx + dy * dy);
    double psi = b.getCamouflage(); // target’s camouflage level ψ

    // 2) Hearing is 360°, so no field-of-view check.
    // 3) Camouflage check: γ > ψ required to “hear/detect” the target.
    if (dist <= m_delta && m_gamma > psi) {
      canThisSensorHear = true;
    }
  }

  // The bestiole can detect the target if this sensor can, or if any wrapped sensor can.
  return canThisSensorHear || m_bestiole->canSee(b);
}

bool Ears::detect(IBestiole &b) { return canSee(b); }