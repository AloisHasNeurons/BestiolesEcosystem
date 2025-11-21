#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <iostream>

#include "CImg.h"

using cimg_library::CImgDisplay;

// Forward declarations
class Environment;
class Factory;

/**
 * @class Aquarium
 * @brief Manages the simulation environment and the CImg display window.
 *
 * Inherits from CImgDisplay to handle the visualization and user input loop.
 */
class Aquarium : public CImgDisplay {
 private:
  // The simulation environment containing all bestioles.
  Environment* m_population;
  // The factory responsible for creating bestiole objects.
  Factory* m_factory;
  // The delay in milliseconds between simulation steps.
  int m_delayMs;

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
  Environment& getEnvironment() { return *m_population; }

  /**
   * @brief Starts the main simulation loop.
   *
   * Runs the step-by-step simulation until the display window is closed.
   */
  void run();
};

#endif  // AQUARIUM_H