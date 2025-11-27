#ifndef AQUARIUM_H_
#define AQUARIUM_H_

#include <CImg.h>

#include <iostream>

#include "core/Environment.h"

struct SensorConfig {
  double deltaMin;   // minimum detection distance
  double deltaMax;   // maximum detection distance
  double alphaMin;   // minimum field-of-view angle
  double alphaMax;   // maximum field-of-view angle
  double gammaMin;   // lower bound of detection capability γ
  double gammaMax;   // upper bound of detection capability γ
};

class Aquarium : public cimg_library::CImgDisplay {
 private:
  Environment* population;
  int delay;
  //static double deltaEyeMin, deltaEyeMax, alpha, gammaEyeMin, gammaEyeMMax; // Vision parameters
  static SensorConfig eyeConfig; 
  static SensorConfig earConfig;

 public:
  Aquarium(int width, int height, int _delay);
  ~Aquarium(void);

  Environment& getEnvironment(void) { return *population; }
  void run(void);

  static const SensorConfig& getEyeConfig() { return eyeConfig; }
  static void setEyeConfig(const SensorConfig& cfg) { eyeConfig = cfg; }

  static const SensorConfig& getEarConfig() { return earConfig; }
  static void setEarConfig(const SensorConfig& cfg) { earConfig = cfg; }
};

#endif