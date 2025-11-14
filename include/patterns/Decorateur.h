#ifndef DECORATOR_H
#define DECORATOR_H

#include "interfaces/IBestiole.h"

// Base class for decorators
class Decorator : public IBestiole {
 public:
  explicit Decorator(IBestiole* bestiole) : m_bestiole(bestiole) {}
  virtual ~Decorator() { delete m_bestiole; }

  // Default implementation: delegate to the decorated bestiole
  void action(Environment& environment) override {
    m_bestiole->action(environment);
  }
  void draw(UImg& img) override { m_bestiole->draw(img); }
  void initCoords(int x, int y) override { m_bestiole->initCoords(x, y); }

  IBestiole* clone() override {
    // A clone must clone the bestiole AND the decorator
    return new Decorator(m_bestiole->clone());
  }

  bool collision() override { return m_bestiole->collision(); }
  void kill(int delay) override { m_bestiole->kill(delay); }

  bool canSee(const IBestiole& b) const override {
    return m_bestiole->canSee(b);
  }

  int getX() const override { return m_bestiole->getX(); }
  int getY() const override { return m_bestiole->getY(); }

 protected:
  IBestiole* m_bestiole;
};

#endif  // DECORATOR_H