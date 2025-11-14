#ifndef DECORATEUR_H
#define DECORATEUR_H

#include "interfaces/IBestiole.h"

// Classe de base pour les décorateurs
class Decorateur : public IBestiole {
 public:
 explicit Decorateur(IBestiole* bestiole) : m_bestiole(bestiole) {}
 virtual ~Decorateur() { delete m_bestiole; }

  // Implémentation par défaut : déléguer à la bestiole décorée
  void action(Milieu& milieu) override { m_bestiole->action(milieu); }
  void draw(UImg& img) override { m_bestiole->draw(img); }
  void initCoords(int x, int y) override { m_bestiole->initCoords(x, y); }

  IBestiole* clone() override {
    // Un clone doit cloner la bestiole ET le décorateur
    return new Decorateur(m_bestiole->clone());
  }

  bool collision() override { return m_bestiole->collision(); }
  void kill(int delay) override { m_bestiole->kill(delay); }

  bool jeTeVois(const IBestiole& b) const override {
    return m_bestiole->jeTeVois(b);
  }

  int getX() const override { return m_bestiole->getX(); }
  int getY() const override { return m_bestiole->getY(); }

 protected:
  IBestiole* m_bestiole;
};

#endif  // DECORATEUR_H