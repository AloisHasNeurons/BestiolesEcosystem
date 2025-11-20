#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <iostream>
#include <memory>
#include <vector>
#include <map>

#include "../UImg.h"
#include "interfaces/IBestiole.h"

class Environment : public UImg {
 private:
  static const T white[];

  std::map<std::string, double> behaviorDistribution = { // Adds up to 1.0
    {"Anticipating", 0.2},
    {"Fearfull", 0.1},
    {"Gregarious", 0.3},
    {"Kamikaze", 0.25},
    {"MultiPersonality", 0.15}
  }; // Behavior distribution map for Factory pattern ((can be modified later))


  std::vector<IBestiole*> bestiolesList;

 public:
  Environment(int _width, int _height);
  ~Environment();

  void step(void);

  void addMember(IBestiole* b) {
    bestiolesList.push_back(b); // Add bestiole to the list
    b->initCoords(this->width(), this->height());
  }

  int neighborCount(const IBestiole& b);

  std::vector<double> getBehaviorDistribution() const { 
    std::vector<double> probs; // Vector to hold probabilities
    for (const auto& pair : behaviorDistribution) { // Iterate through the map
      probs.push_back(pair.second); // Add probability to vector
    }
    return probs;
  }
};

#endif