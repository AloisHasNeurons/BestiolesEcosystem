#ifndef FEARFUL_H
#define FEARFUL_H

#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

class IBestiole;

class Fearful : public IBehavior {
 private:
  int max_neighbors;
  unsigned char* color =
      new unsigned char[3]{0, 0, 255};  // Blue color for Fearful behavior
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  Fearful(int max_neighbors = 1) : max_neighbors(max_neighbors) {}
  Fearful(const Fearful& other) {
    max_neighbors = other.max_neighbors;
    color = other.color;
  }
  IBehavior* clone() const override { return new Fearful(*this); }
  std::string getName() const override { return "Fearful"; }
  unsigned char* getColor() const override { return color; }
};

#endif  // FEARFUL_H