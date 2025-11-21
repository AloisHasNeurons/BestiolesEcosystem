#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <iostream>
#include <memory>
#include <vector>
#include <map>


#include "../UImg.h"
#include "interfaces/IBestiole.h"
#include "core/Bestiole.h"
#include "patterns/IFactory.h"

class Environment : public UImg {
 private:
  static const T white[];
  static double birthRate; // Birth rate of bestioles
  static double deltaEyeMin, deltaEyeMax, alpha, gammaEyeMin, gammaEyeMMax; // Vision parameters
  

  std::map<std::string, double> behaviorDistribution = { // Adds up to 1.0
    {"Anticipating", 0.2},
    {"Fearfull", 0.1},
    {"Gregarious", 0.3},
    {"Kamikaze", 0.25},
    {"MultiPersonality", 0.15}
  }; // Behavior distribution map for Factory pattern ((can be modified later))

  IFactory& factory; // Factory 
  std::vector<IBestiole*> bestiolesList;

 public:
  Environment(int _width, int _height, IFactory& f);
  ~Environment();
  Environment(IFactory& f);

  void step(void);

  void addMember(IBestiole* b);

  int neighborCount(const IBestiole& b);

  // Getters in .h because they are simple and inline enough
  std::vector<double> getBehaviorDistribution() const;
  std::vector<IBestiole*> getBestiolesList() const;

  double getDeltaEyeMin() const {
    return deltaEyeMin;
  }

  double getDeltaEyeMax() const {
    return deltaEyeMax;
  }

  double getAlpha() const {
    return alpha;
  }

  double getGammaEyeMin() const {
    return gammaEyeMin;
  }

  double getGammaEyeMMax() const {
    return gammaEyeMMax;
  }

  // Setters in .h because they are simple and inline enough
  void setBehaviorDistribution(const std::map<std::string, double>& newDistribution) {
    behaviorDistribution = newDistribution; // Update the behavior distribution map
  }

  void setBirthRate(double rate) {
    birthRate = rate;
  }

  void setVisionParameters(double deltaMin, double deltaMax, double alphaVal, double gammaMin, double gammaMax) {
    deltaEyeMin = deltaMin;
    deltaEyeMax = deltaMax;
    alpha = alphaVal;
    gammaEyeMin = gammaMin;
    gammaEyeMMax = gammaMax;
  }
};

#endif