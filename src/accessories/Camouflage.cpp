#include "accessories/Camouflage.h"
#include <cmath>
#include <random>
#include "core/Aquarium.h"

std::string Camouflage::getDescription() const {
    return "Camouflage + " + m_bestiole->getDescription();
}


IBestiole* Camouflage::clone() {
  // Must wrap the inner clone with new Camouflage(...)
  return new Camouflage(m_bestiole->clone());
}


Camouflage::Camouflage(IBestiole *b) : IAccessory(b) {
  // Set the camouflage value of the bestiole
  // chose random psi value based on environment configuration
  double r = static_cast<double>(std::rand()) / RAND_MAX;
  m_psi = Aquarium::getAccessoryConfig().camouflageMin +
        r * (Aquarium::getAccessoryConfig().camouflageMax -
             Aquarium::getAccessoryConfig().camouflageMin);
}

void Camouflage::action(Environment &env, IBestiole* self = nullptr) {
  // Delegate the action to the wrapped object, passing along the 'self' pointer.
  m_bestiole->action(env, self);
}

void Camouflage::draw(UImg &img) {
  Decorator::draw(img);

  // Add an additional semi-transparent overlay to simulate blending with the
  // background
  int cx = getX();
  int cy = getY();
  double theta = getOrientation();
  double size = getSize();

  double angleDeg = -theta * 180.0 / M_PI;

  // To simulate camouflage, draw a semi-transparent overlay using the
  // background color. This "washes out" the bestiole's original color,
  // making it blend in. The background is white.
  T backgroundColor[3] = {255, 255, 255};

  // The opacity of the overlay is determined by the camouflage strength (m_psi).
  // A higher psi value results in a more opaque overlay, making the bestiole
  // harder to see. We clamp it to a max value to prevent total invisibility.
  float alpha = std::min(0.8f, static_cast<float>(m_psi));

  img.draw_ellipse(cx, cy, size, size / 5.0, angleDeg, backgroundColor, alpha);
}

double Camouflage::getCamouflage() const {
  // As a decorator, add this layer's camouflage value to the value of the
  // wrapped object. This allows multiple camouflage effects to stack correctly.
  return m_psi + m_bestiole->getCamouflage();
}