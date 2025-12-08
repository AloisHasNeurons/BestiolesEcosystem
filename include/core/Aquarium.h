#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <iostream>

#include "CImg.h"
#include "core/Environment.h"

using cimg_library::CImgDisplay;

// Forward declarations
class Environment;
class Factory;

struct SensorConfig {
  double deltaMin = 30.0; // minimum detection distance
  double deltaMax = 100.0; // maximum detection distance
  double alphaMin = 90.0; // minimum field-of-view angle in degrees
  double alphaMax = 270.0; // maximum field-of-view angle in degrees
  double gammaMin = 0.5; // lower bound of detection capability γ
  double gammaMax = 1.0; // upper bound of detection capability γ
};

struct AccessoryConfig {

  double camouflageMin; // minimum camouflage value

  double camouflageMax; // maximum camouflage value

  double nuMin = 1.0; // minimum speed factor for Fin accessory

  double nuMax; // maximum speed factor for Fin accessory

  double tetaMin = 1.0; // minimum speed reduction factor for Shell accessory

  double tetaMax; // maximum speed reduction factor for Shell accessory

  double omegaMin = 1.0; // minimum armor enhancement factor for Shell accessory

  double omegaMax; // maximum armor enhancement factor for Shell accessory
};

/**
 * @class Aquarium
 * @brief Manages the simulation environment and the CImg display window.
 *
 * Inherits from CImgDisplay to handle the visualization and user input loop.
 */
class Aquarium : public CImgDisplay {
private:
  // The simulation environment containing all bestioles.
  Environment *m_population;
  // The factory responsible for creating bestiole objects.
  Factory *m_factory;
  // The delay in milliseconds between simulation steps.
  int m_delayMs;

  static SensorConfig eyeConfig;

  static SensorConfig earConfig;

  static AccessoryConfig accessoryConfig;

public:
  /**
   * @brief Constructor for the Aquarium.
   *
   * @param kWidth The width of the display area.
   * @param kHeight The height of the display area.
   * @param kDelayMs The delay in milliseconds per step (renamed from '_delay').
   */
  Aquarium(int kWidth, int kHeight, int kDelayMs);

  /**
   * @brief Destructor.
   *
   * Handles cleanup of dynamically allocated members (`m_population` and
   * `m_factory`).
   */
  ~Aquarium();

  /**
   * @brief Gets a reference to the simulation environment.
   *
   * @return Environment& Reference to the Environment object.
   */
  Environment &getEnvironment() { return *m_population; }

  /**
   * @brief Starts the main simulation loop.
   *
   * Runs the step-by-step simulation until the display window is closed.
   */
  void run();

  static const SensorConfig &getEyeConfig() { return eyeConfig; }

  static void setEyeConfig(const SensorConfig &cfg) { eyeConfig = cfg; }

  static const SensorConfig &getEarConfig() { return earConfig; }

  static void setEarConfig(const SensorConfig &cfg) { earConfig = cfg; }

  static AccessoryConfig getAccessoryConfig() { return accessoryConfig; }

  static void setAccessoryConfig(const AccessoryConfig &cfg) {
    accessoryConfig = cfg;
  }
};

#endif // AQUARIUM_H