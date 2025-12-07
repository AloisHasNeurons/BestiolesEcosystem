#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <chrono>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "../UImg.h"
#include "core/Bestiole.h"
#include "core/StatsCollector.h"
#include "interfaces/IBestiole.h"
#include "patterns/Factory.h"

/**
 * @class Environment
 * @brief Represents the simulation space and manages the collection of
 * bestioles.
 *
 * Inherits from UImg to provide drawing capabilities for the simulation area.
 */
class Environment : public UImg {
private:
  // --- Static Members (k prefix) ---
  static const T kBackgroundColor[]; // Background color (white)
  // Birth rate (probability) of bestioles per step
  static double kBirthRateProbability;

  // Map defining the probability distribution for bestiole creation by the
  // factory
  std::map<std::string, double> m_behaviorDistribution = {
      // Adds up to 1.0
      {"Anticipating", 0},
      {"Fearfull", 0},
      {"Gregarious", 1},
      {"Kamikaze", 0},
      {"MultiPersonality", 0}};
  std::map<std::string, double> eyesAccessoryDistribution = {

      {"NoEyes", 1},

      {"WithEyes", 0}

  }; // Accessory distribution map for Eyes decorator

  std::map<std::string, double> earsAccessoryDistribution = {

      {"NoEars", 0},

      {"WithEars", 1}

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

  // Reference to the factory used to create members
  IFactory &m_factory;

  // Main list of all bestioles currently active in the environment
  std::vector<IBestiole *> m_bestiolesList;
  // Temporary list to hold new bestioles created during a step, added in the
  // next step
  std::vector<IBestiole *> m_bestiolesToAdd;

  StatsCollector m_statsCollector;
  int m_stepCount;
  std::chrono::steady_clock::time_point m_lastSummaryTime;
  double m_summaryIntervalSeconds = 2.0;

public:
  /**
   * @brief Constructor with specified dimensions.
   *
   * @param kWidth The width of the environment (renamed from '_width').
   * @param kHeight The height of the environment (renamed from '_height').
   * @param factoryRef The factory used to create IBestiole objects (renamed
   * from 'f').
   */
  Environment(int kWidth, int kHeight, IFactory &factoryRef);

  /**
   * @brief Destructor.
   *
   * Clears the lists and deletes all contained IBestiole objects.
   */
  ~Environment();

  /**
   * @brief Constructor using default dimensions.
   *
   * @param factoryRef The factory used to create IBestiole objects (renamed
   * from 'f').
   */
  explicit Environment(IFactory &factoryRef);

  /**
   * @brief Executes one step of the environment simulation.
   *
   * Updates all bestioles, handles death, collisions, and birth probability.
   * @param void No parameters.
   */
  void step(void);

  /**
   * @brief Adds a new IBestiole member to the environment (via the pending
   * list).
   *
   * @param bestiole A pointer to the IBestiole to add (renamed from 'b').
   */
  void addMember(IBestiole *bestiole);

  /**
   * @brief Counts the number of visible neighbors for a given bestiole.
   *
   * @param currentBestiole The bestiole whose neighbors are being counted
   * (renamed from 'b').
   * @return The number of neighboring bestioles visible to `currentBestiole`.
   */
  int neighborCount(const IBestiole &currentBestiole);
  void recordEvent(const std::string &event);

  // --- Getters (Simple/Inline) ---

  /**
   * @brief Retrieves the distribution probabilities of the defined behaviors.
   * @return A vector of doubles representing the probabilities.
   */
  std::vector<double> getBehaviorDistribution() const;

  /**
   * @brief Gets the list of all active bestioles in the environment.
   * @return std::vector<IBestiole*> The list of bestioles.
   */
  std::vector<IBestiole *> getBestiolesList() const { return m_bestiolesList; }

  // -- getters for accessory distributions --
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

  // --- Setters (Simple/Inline) ---

  /**
   * @brief Sets a new behavior distribution map.
   * @param newDistribution The new map of behavior names to probabilities.
   */
  void setBehaviorDistribution(
      const std::map<std::string, double> &newDistribution) {
    m_behaviorDistribution = newDistribution;
  }

  /**
   * @brief Sets the probability of new bestiole birth per step.
   * @param rate The new birth rate (0.0 to 1.0).
   */
  void setBirthRateProbability(double rate) { kBirthRateProbability = rate; }

  // Setters for accessory distributions
  void setEyesAccessoryDistribution(
      const std::map<std::string, double>& dist) {
    eyesAccessoryDistribution = dist;
  }
  void setEarsAccessoryDistribution(
      const std::map<std::string, double>& dist) {
    earsAccessoryDistribution = dist;
  }
  void setCamouflageAccessoryDistribution(
      const std::map<std::string, double>& dist) {
    camouflageAccessoryDistribution = dist;
  }
  void setFinsAccessoryDistribution(
      const std::map<std::string, double>& dist) {
    finsAccessoryDistribution = dist;
  }
  void setShellAccessoryDistribution(
      const std::map<std::string, double>& dist) {
    shellAccessoryDistribution = dist;
  }

  // Method to reset/clear population
  void resetPopulation() {
      for (IBestiole* b : m_bestiolesList) {
          delete b;
      }
      m_bestiolesList.clear();
      // Also clear pending inclusions
      for (IBestiole* b : m_bestiolesToAdd) {
          delete b;
      }
      m_bestiolesToAdd.clear();
  }

  // Method to spawn initial population again
  void spawnPopulation(int count) {
      for (int i = 0; i < count; ++i) {
          addMember(m_factory.createBestiole());
      }
  }

};

#endif // ENVIRONMENT_H_