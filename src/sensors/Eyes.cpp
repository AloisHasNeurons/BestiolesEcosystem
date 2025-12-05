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

IBestiole *Eyes::clone() {
  // Wrap the inner clone with a new Eyes decorator
  return new Eyes(m_bestiole->clone());
}

std::string Eyes::getDescription() const {
  // Add "Eyes" to the description chain
  return "Eyes + " + m_bestiole->getDescription();
}

bool Eyes::canSee(const IBestiole &b) const {
  // Check if this specific sensor (Eyes) can see the target.
  bool canThisSensorSee = false;
  {
    // 1) Distance check: must be within seeing distance m_delta.
    double x1 = static_cast<double>(getX());
    double y1 = static_cast<double>(getY());
    double x2 = static_cast<double>(b.getX());
    double y2 = static_cast<double>(b.getY());
    double dx = x2 - x1;
    double dy = y1 - y2; // screen coordinates: y increases downward
    double dist = std::sqrt(dx * dx + dy * dy);

    // 2) Field-of-view and Camouflage checks are only performed if within distance.
    if (dist <= m_delta) {
      double theta = getOrientation();      // my orientation
      double angleToB = std::atan2(dy, dx); // direction toward the target
      double dTheta = std::atan2(std::sin(angleToB - theta), std::cos(angleToB - theta));
      double psi = b.getCamouflage(); // camouflage strength of the target

      if (std::fabs(dTheta) <= m_alpha * 0.5 && m_gamma > psi) {
        canThisSensorSee = true;
      }
    }
  }

  // The bestiole can see the target if this sensor can, or if any wrapped sensor can.
  return canThisSensorSee || m_bestiole->canSee(b);
}

bool Eyes::detect(IBestiole &b) { return canSee(b); }