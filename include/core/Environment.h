#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "../UImg.h"
#include "interfaces/IBestiole.h"

class Environment : public UImg {
 private:
  static const T white[];
  static double birthRate;  // Birth rate of bestioles
  static double cloneRate;  // Clone rate of bestioles
  static double deltaEyeMin, deltaEyeMax, alpha, gammaEyeMin,
      gammaEyeMMax;  // Vision parameters

  std::map<std::string, double> behaviorDistribution = {
      // Adds up to 1.0
      {"Anticipating", 0.2},
      {"Fearfull", 0.1},
      {"Gregarious", 0.3},
      {"Kamikaze", 0.25},
      {"MultiPersonality", 0.15}};  // Behavior distribution map for Factory
                                    // pattern ((can be modified later))

  std::vector<IBestiole*> bestiolesList;

 public:
  Environment(int _width, int _height);
  ~Environment();

  void step(void);

  void addMember(IBestiole* b) {
    bestiolesList.push_back(b);  // Add bestiole to the list
    b->initCoords(this->width(), this->height());
  }

  int neighborCount(const IBestiole& b);

  // Getters in .h because they are simple and inline enough
  std::vector<double> getBehaviorDistribution() const {
    std::vector<double> probs;  // Vector to hold probabilities
    for (const auto& pair : behaviorDistribution) {  // Iterate through the map
      probs.push_back(pair.second);  // Add probability to vector
    }
    return probs;
  }
  std::vector<IBestiole*> getBestiolesList() const { return bestiolesList; }

  // Setters
  void setBehaviorDistribution(
      const std::map<std::string, double>& newDistribution) {
    behaviorDistribution =
        newDistribution;  // Update the behavior distribution map
  }

  void setBirthRate(double rate) { birthRate = rate; }
  void setCloneRate(double rate) { cloneRate = rate; }

  void setVisionParameters(double deltaMin, double deltaMax, double alphaVal,
                           double gammaMin, double gammaMax) {
    deltaEyeMin = deltaMin;
    deltaEyeMax = deltaMax;
    alpha = alphaVal;
    gammaEyeMin = gammaMin;
    gammaEyeMMax = gammaMax;
  }
};

#endif