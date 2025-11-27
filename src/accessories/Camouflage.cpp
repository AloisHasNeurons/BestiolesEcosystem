#include "Camouflage.h"
#include <cmath>

Camouflage::Camouflage(IBestiole* b, double _psi)
    : IAccessory(b), psi(_psi)
{
  // Set the camouflage value of the bestiole
  m_bestiole->setCamouflage(psi);
}

void Camouflage::move(Environment& env)
{
  // Camouflage does not alter movement behavior; simply forward the action
  m_bestiole->action(env);
}

void Camouflage::draw(UImg& img)
{
  IAccessory::draw(img);

  // Add an additional semi-transparent overlay to simulate blending with the background
  int cx = getX();
  int cy = getY();
  double theta = getOrientation();
  double size = getSize();

  double angleDeg = -theta * 180.0 / M_PI;

  // Camouflage color: a light tone leaning toward the background (adjust if needed)
  T camoColor[3] = {200, 220, 200};

  // Use low opacity so the body appears blended into the environment
  // Note: the last argument of draw_ellipse is alpha (0.0–1.0)
  img.draw_ellipse(cx, cy, size, size / 5.0, angleDeg, camoColor, 0.3f);
}

double Camouflage::getCamouflage() const
{
  // Override IBestiole's default getCamouflage()
  return psi;
}
