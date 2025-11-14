#ifndef IBESTIOLE_H
#define IBESTIOLE_H

#include "IsKillable.h"

// Déclarations anticipées (Forward declarations)
class Milieu;
class UImg;

class IBestiole : public IsKillable {
 public:
  virtual ~IBestiole() {}

  // Méthodes de l'interface
  virtual void action(Milieu& milieu) = 0;
  virtual void draw(UImg& img) = 0;
  virtual void initCoords(int x, int y) = 0;
  virtual IBestiole* clone() = 0;
  virtual bool collision() = 0;
  virtual bool jeTeVois(const Bestiole& b) const = 0;

  // Méthode héritée de IsKillable
  virtual void kill(int delay) override = 0;
};

#endif  // IBESTIOLE_H