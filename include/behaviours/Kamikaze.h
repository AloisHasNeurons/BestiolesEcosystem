#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "../interfaces/IBehavior.h"
#include <vector>
#include <string>

class Bestiole;

class Kamikaze : public IBehavior {
 private:
  unsigned char* color = new unsigned char[3]{255, 0, 0}; // Red color for Kamikaze bestioles
 public:
  double steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  double speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) override;
  Kamikaze() {}
  Kamikaze(const Kamikaze& other) { color = other.color; }
  IBehavior* clone() const override {
      return new Kamikaze(*this);
  }
  std::string getName() const override { 
      return "Kamikaze"; 
  }
};

#endif  // KAMIKAZE_H