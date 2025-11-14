#ifndef DECORATEUR_H
#define DECORATEUR_H

#include "../interfaces/IBestiole.h"

// Classe de base pour les décorateurs
class Decorateur : public IBestiole {
 public:
  Decorateur(IBestiole* bestiole) : m_bestiole(bestiole) {}
  virtual ~Decorateur() {
    delete m_bestiole;
  }  // Le décorateur gère la bestiole décorée

  // Implémentation par défaut : déléguer à la bestiole décorée
  void action(Milieu& milieu) override { m_bestiole->action(milieu); }
  void draw(UImg& img) override { m_bestiole->draw(img); }
  void initCoords(int x, int y) override { m_bestiole->initCoords(x, y); }
  IBestiole* clone() override { /* Doit être implémenté avec soin */
    return nullptr;
  }
  bool collision() override { return m_bestiole->collision(); }
  bool JeTeVois() override { return m_bestiole->JeTeVois(); }
  void kill(int delay) override { m_bestiole->kill(delay); }

 protected:
  IBestiole* m_bestiole;
};

#endif  // DECORATEUR_H