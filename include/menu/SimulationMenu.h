#ifndef SIMULATION_MENU_H
#define SIMULATION_MENU_H

#include <map>
#include <string>

#include "menu/SimulationConfig.h"

class SimulationMenu {
 public:
  SimulationMenu();
  void run(SimulationConfig &config);

 private:
  void clearScreen();
  int getIntInput(const std::string &prompt, int defaultValue = -1);
  double getDoubleInput(const std::string &prompt, double defaultValue = -1.0);

  void configurePhysics(SimulationConfig &config);
  void configurePopulation(SimulationConfig &config);
  void configureProbabilities(SimulationConfig &config);
  void configureAccessories(SimulationConfig &config);

  bool validateProbabilities(const std::map<std::string, double> &dist);
};

#endif  // SIMULATION_MENU_H
