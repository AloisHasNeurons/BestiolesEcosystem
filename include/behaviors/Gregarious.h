#ifndef GREGARIOUS_H
#define GREGARIOUS_H

#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

class IBestiole;

class Gregarious : public IBehavior {
 private:
  unsigned char* color =
      new unsigned char[3]{0, 255, 0};  // Green color for Gregarious bestioles
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  Gregarious() {}
  Gregarious(const Gregarious& other) { color = other.color; }
  IBehavior* clone() const override { return new Gregarious(*this); }
  std::string getName() const override { return "Gregarious"; }
  unsigned char* getColor() const override { return color; }
};

#endif  // GREGARIOUS_H