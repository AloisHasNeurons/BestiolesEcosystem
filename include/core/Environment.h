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

struct SensorConfig {
    double deltaMin;   // 距离最小值
    double deltaMax;   // 距离最大值
    double alphaMin;   // 视场角最小值（度数或弧度，看你约定）
    double alphaMax;   // 视场角最大值
    double gammaMin;   // 检测能力 γ 下限
    double gammaMax;   // 检测能力 γ 上限
};

class Environment : public UImg {
 private:
  static const T white[];
  static double birthRate; // Birth rate of bestioles
  //static double deltaEyeMin, deltaEyeMax, alpha, gammaEyeMin, gammaEyeMMax; // Vision parameters
  static SensorConfig eyeConfig; 
  static SensorConfig earConfig;

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

  // Setters in .h because they are simple and inline enough
  void setBehaviorDistribution(const std::map<std::string, double>& newDistribution) {
    behaviorDistribution = newDistribution; // Update the behavior distribution map
  }

  void setBirthRate(double rate) {
    birthRate = rate;
  }

  static const SensorConfig& getEyeConfig() { return eyeConfig; }
  static void setEyeConfig(const SensorConfig& cfg) { eyeConfig = cfg; }

  static const SensorConfig& getEarConfig() { return earConfig; }
  static void setEarConfig(const SensorConfig& cfg) { earConfig = cfg; }

  //

  void setVisionParameters(double deltaMin, double deltaMax,
                           double alphaMin, double alphaMax,
                           double gammaMin, double gammaMax) {
    SensorConfig cfg { deltaMin, deltaMax, alphaMin, alphaMax, gammaMin, gammaMax };
    setEyeConfig(cfg);
  }
};

#endif