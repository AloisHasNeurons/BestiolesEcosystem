#ifndef BESTIOLE_H
#define BESTIOLE_H

#include <memory>

#include "../interfaces/IBestiole.h"
#include "UImg.h"

using namespace std;

class Milieu;
class IComportement;

class Bestiole : public IBestiole {
 private:
  static const double AFF_SIZE;
  static const double MAX_VITESSE;
  static const double LIMITE_VUE;
  static int next;

 private:
  int identite;
  int x, y;
  double cumulX, cumulY;
  double orientation;
  double vitesse;

  T* couleur;

  double resistance;
  double opacite;
  int dureeVie;

  std::unique_ptr<IComportement> comportement;

 private:
  void bouge(int xLim, int yLim);

 public:
  Bestiole(void);               // Constructeur par defaut
  Bestiole(const Bestiole& b);  // Constructeur de copies
  ~Bestiole(void);              // Destructeur

  void action(Milieu& monMilieu) override;
  void draw(UImg& support) override;
  void initCoords(int xLim, int yLim) override;

  IBestiole* clone() override;
  bool collision() override;
  void kill(int delay) override;
  bool jeTeVois(const Bestiole& b) const;

  friend bool operator==(const Bestiole& b1, const Bestiole& b2);
};

#endif