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

  std::map<std::string, double> behaviorDistribution = { // Adds up to 1.0
    {"Anticipating", 0.2},
    {"Fearfull", 0.1},
    {"Gregarious", 0.3},
    {"Kamikaze", 0.25},
    {"MultiPersonality", 0.15}
  }; // Behavior distribution map for Factory pattern ((can be modified later))

  std::map<std::string, double> eyesAccessoryDistribution = {
    {"NoEyes", 0.7},
    {"WithEyes", 0.3}
  }; // Accessory distribution map for Eyes decorator

  std::map<std::string, double> earsAccessoryDistribution = {
    {"NoEars", 0.6},
    {"WithEars", 0.4}
  }; // Accessory distribution map for Ears decorator

  std::map<std::string, double> camouflageAccessoryDistribution = {
    {"NoCamouflage", 0.8},
    {"WithCamouflage", 0.2}
  }; // Accessory distribution map for Camouflage decorator

  std::map<std::string, double> finsAccessoryDistribution = {
    {"NoFins", 0.7},
    {"WithFins", 0.3}
  }; // Accessory distribution map for Fins decorator

  std::map<std::string, double> shellAccessoryDistribution = {
    {"NoShell", 0.85},
    {"WithShell", 0.15}
  }; // Accessory distribution map for Shell decorator

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
  std::map<std::string, double> getEyesAccessoryDistribution() const {
    return eyesAccessoryDistribution;
  }
  std::map<std::string, double> getEarsAccessoryDistribution() const {
    return earsAccessoryDistribution;
  }
  std::map<std::string, double> getCamouflageAccessoryDistribution() const {
    return camouflageAccessoryDistribution;
  }
  std::map<std::string, double> getFinsAccessoryDistribution() const {
    return finsAccessoryDistribution;
  }
  std::map<std::string, double> getShellAccessoryDistribution() const {
    return shellAccessoryDistribution;
  }

  // Setters in .h because they are simple and inline enough
  void setBehaviorDistribution(const std::map<std::string, double>& newDistribution) {
    behaviorDistribution = newDistribution; // Update the behavior distribution map
  }

  void setBirthRate(double rate) {
    birthRate = rate;
  }

};

#endif