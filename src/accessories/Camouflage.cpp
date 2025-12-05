#include "accessories/Camouflage.h"
#include <cmath>
#include <random>
#include "core/Aquarium.h"

Camouflage::Camouflage(IBestiole *b) : IAccessory(b) {
  // Set the camouflage value of the bestiole
  // chose random psi value based on environment configuration
  double r = static_cast<double>(std::rand()) / RAND_MAX;
  m_psi = Aquarium::getAccessoryConfig().camouflageMin +
        r * (Aquarium::getAccessoryConfig().camouflageMax -
             Aquarium::getAccessoryConfig().camouflageMin);
}

Camouflage::Camouflage(const Camouflage &other, IBestiole *inner)
    : IAccessory(inner), m_psi(other.m_psi) {
}

IBestiole *Camouflage::clone() {
  return new Camouflage(*this, m_bestiole->clone());
}

void Camouflage::action(Environment &env) {
  // Camouflage does not alter movement behavior; simply forward the action
  m_bestiole->action(env);
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

  // Camouflage color: a light tone leaning toward the background (adjust if
  // needed)
  T camoColor[3] = {200, 220, 200};

  // Use low opacity so the body appears blended into the environment
  // Note: the last argument of draw_ellipse is alpha (0.0–1.0)
  img.draw_ellipse(cx, cy, size, size / 5.0, angleDeg, camoColor, 0.3f);
}

double Camouflage::getCamouflage() const {
  // Override IBestiole's default getCamouflage()
  return m_psi;
}