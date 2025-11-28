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
#include "interfaces/IBestiole.h"
#include "core/StatsCollector.h"
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
  static const T kWhite[];   // Background color (white)
  static double kBirthRate;  // Birth rate (probability) of bestioles per step
                             // (renamed from 'birthRate')
  // Vision parameters (renamed from 'deltaEyeMin', etc.)
  static double kDeltaEyeMin, kDeltaEyeMax, kAlpha, kGammaEyeMin, kGammaEyeMax;

  // Map defining the probability distribution for bestiole creation by the
  // factory
  std::map<std::string, double> m_behaviorDistribution = {
      // Adds up to 1.0
      {"Anticipating", 0.2},
      {"Fearfull", 0.1},
      {"Gregarious", 0.3},
      {"Kamikaze", 0.25},
      {"MultiPersonality", 0.15}};

  // Reference to the factory used to create members
  IFactory& m_factory;

  // Main list of all bestioles currently active in the environment
  std::vector<IBestiole*> m_bestiolesList;
  // Temporary list to hold new bestioles created during a step, added in the
  // next step
  std::vector<IBestiole*> m_bestiolesToAdd;

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
  Environment(int kWidth, int kHeight, IFactory& factoryRef);

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
  explicit Environment(IFactory& factoryRef);

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
  void addMember(IBestiole* bestiole);

  /**
   * @brief Counts the number of visible neighbors for a given bestiole.
   *
   * @param currentBestiole The bestiole whose neighbors are being counted
   * (renamed from 'b').
   * @return The number of neighboring bestioles visible to `currentBestiole`.
   */
  int neighborCount(const IBestiole& currentBestiole);
  void recordEvent(const std::string& event);

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
  std::vector<IBestiole*> getBestiolesList() const { return m_bestiolesList; }

  /**
   * @brief Gets the minimum eye angle difference for perception.
   * @return double The minimum delta eye angle.
   */
  double getDeltaEyeMin() const { return kDeltaEyeMin; }

  /**
   * @brief Gets the maximum eye angle difference for perception.
   * @return double The maximum delta eye angle.
   */
  double getDeltaEyeMax() const { return kDeltaEyeMax; }

  /**
   * @brief Gets the alpha parameter for vision.
   * @return double The alpha value.
   */
  double getAlpha() const { return kAlpha; }

  /**
   * @brief Gets the minimum eye distance/range parameter.
   * @return double The minimum gamma eye distance.
   */
  double getGammaEyeMin() const { return kGammaEyeMin; }

  /**
   * @brief Gets the maximum eye distance/range parameter.
   * @return double The maximum gamma eye distance (renamed from
   * 'gammaEyeMMax').
   */
  double getGammaEyeMax() const { return kGammaEyeMax; }

  // --- Setters (Simple/Inline) ---

  /**
   * @brief Sets a new behavior distribution map.
   * @param newDistribution The new map of behavior names to probabilities.
   */
  void setBehaviorDistribution(
      const std::map<std::string, double>& newDistribution) {
    m_behaviorDistribution = newDistribution;
  }

  /**
   * @brief Sets the probability of new bestiole birth per step.
   * @param rate The new birth rate (0.0 to 1.0).
   */
  void setBirthRate(double rate) { kBirthRate = rate; }

  /**
   * @brief Sets all vision parameters simultaneously.
   * @param deltaMin The new minimum delta eye angle.
   * @param deltaMax The new maximum delta eye angle.
   * @param alphaVal The new alpha value.
   * @param gammaMin The new minimum gamma eye distance.
   * @param gammaMax The new maximum gamma eye distance (renamed from
   * 'gammaEyeMMax').
   */
  void setVisionParameters(double deltaMin, double deltaMax, double alphaVal,
                           double gammaMin, double gammaMax) {
    kDeltaEyeMin = deltaMin;
    kDeltaEyeMax = deltaMax;
    kAlpha = alphaVal;
    kGammaEyeMin = gammaMin;
    kGammaEyeMax = gammaMax;
  }
};

#endif  // ENVIRONMENT_H_