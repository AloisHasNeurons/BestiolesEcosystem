#ifndef DECORATOR_H
#define DECORATOR_H

#include "interfaces/IBestiole.h"

// Base class for decorators
class Decorator : public IBestiole {
 protected:
 IBestiole* m_bestiole;
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
    // Return a clone of the decorated bestiole (plain Decorator is abstract)
    return m_bestiole->clone();
  }

  bool collision(IBestiole* b, IBestiole* other) override { return m_bestiole->collision(b, other); }
  void kill(int delay) override { m_bestiole->kill(delay); }

  bool canSee(const IBestiole& b) const override {
    return m_bestiole->canSee(b);
  }

  void changeBehavior(std::unique_ptr<IBehavior> behavior) override {
    m_bestiole->changeBehavior(std::move(behavior));
  }

  int getX() const override { return m_bestiole->getX(); }
  int getY() const override { return m_bestiole->getY(); }
  double getOrientation() const override { return m_bestiole->getOrientation(); }
  double getSpeed() const override { return m_bestiole->getSpeed(); }
  double getMaxSpeed() const override { return m_bestiole->getMaxSpeed(); }
  int getLifeSpan() const override { return m_bestiole->getLifeSpan(); }
  double getResistance() const override { return m_bestiole->getResistance(); }
  double getOpacity() const override { return m_bestiole->getOpacity(); }
  IBehavior* getBehavior() const override { return m_bestiole->getBehavior(); }
  std::string getBehaviorString() const override { return m_bestiole->getBehaviorString(); }
  
  // For accessories and sensors' parameters
  double getSize() const override { return m_bestiole->getSize(); }
  double getCamouflage() const override { return m_bestiole->getCamouflage(); }
  double getSpeedFactor() const override { return m_bestiole->getSpeedFactor(); }
  double getArmorFactor() const override { return m_bestiole->getArmorFactor(); }
  void setSpeedFactor(double f) override { m_bestiole->setSpeedFactor(f); } 
  void setArmorFactor(double omega) override { m_bestiole->setArmorFactor(omega); }  
  void setCamouflage(double psi) override { m_bestiole->setCamouflage(psi); }

};

#endif  // DECORATOR_H