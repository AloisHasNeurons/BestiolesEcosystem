#ifndef DECORATOR_H

#define DECORATOR_H

#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../interfaces/IBestiole.h"
#include "../interfaces/IBehavior.h"

// Base class for decorators

class Decorator : public IBestiole {

protected:
  IBestiole *m_bestiole;

public:
  explicit Decorator(IBestiole *bestiole) : m_bestiole(bestiole) {}

  virtual ~Decorator(void);

  // Default implementation: delegate to the decorated bestiole

  void action(Environment &environment, IBestiole *self = nullptr) override {
    m_bestiole->action(environment, self ? self : this);
  }

  void draw(UImg &img) override { m_bestiole->draw(img); }

  void initCoords(int x, int y) override { m_bestiole->initCoords(x, y); }

  IBestiole *clone() override {

    // A clone must clone the bestiole AND the decorator

    return m_bestiole->clone();
  }

  bool collision() override { return m_bestiole->collision(); }

  void kill(int delay) override { m_bestiole->kill(delay); }

  bool canSee(const IBestiole &b) const override {

    return m_bestiole->canSee(b);
  }

  void changeBehavior(std::unique_ptr<IBehavior> behavior) override {

    m_bestiole->changeBehavior(std::move(behavior));
  }

  int getX() const override { return m_bestiole->getX(); }

  int getY() const override { return m_bestiole->getY(); }

  double getOrientation() const override {
    return m_bestiole->getOrientation();
  }

  double getSpeed() const override { return m_bestiole->getSpeed(); }

  double getMaxSpeed() const override { return m_bestiole->getMaxSpeed(); }

  int getLifeSpan() const override { return m_bestiole->getLifeSpan(); }

  double getResistance() const override { return m_bestiole->getResistance(); }

  double getOpacity() const override { return m_bestiole->getOpacity(); }

  IBehavior *getBehavior() const override { return m_bestiole->getBehavior(); }

  std::string getBehaviorString() const override {
    return m_bestiole->getBehaviorString();
  }

  // For accessories and sensors' parameters

  double getSize() const override { return m_bestiole->getSize(); }

  double getCamouflage() const override { return m_bestiole->getCamouflage(); }

  double getSpeedFactor() const override {
    return m_bestiole->getSpeedFactor();
  }

  double getArmorFactor() const override {
    return m_bestiole->getArmorFactor();
  }

  void setSpeedFactor(double f) override { m_bestiole->setSpeedFactor(f); }

  void setArmorFactor(double omega) override {
    m_bestiole->setArmorFactor(omega);
  }

  void setCamouflage(double psi) override { m_bestiole->setCamouflage(psi); }

  void setCloneRate(double newCloneRate) override {
    m_bestiole->setCloneRate(newCloneRate);
  }

  void setOrientation(double o) override { m_bestiole->setOrientation(o); }

  std::vector<std::string> getAccessories() const override {
    return m_bestiole->getAccessories();
  }

  std::vector<std::string> getSensors() const override {
    return m_bestiole->getSensors();
  }
};

#endif // DECORATOR_H