#ifndef MULTIPERSONALITY_H
#define MULTIPERSONALITY_H

#include <chrono>
#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

// Forward declaration of the interface class
class IBestiole;

/**
 * @class MultiPersonality
 * @brief Represents a composite behavior that changes its underlying behavior
 * periodically.
 *
 * The bestiole exhibiting this behavior will switch between different
 * concrete behaviors (e.g., Gregarious, Fearful) over time.
 */
class MultiPersonality : public IBehavior {
 private:
  // Pointer to the currently active concrete behavior.
  IBehavior* m_currentBehavior;
  // Timestamp of the last time the behavior was changed.
  std::chrono::steady_clock::time_point m_lastChange;

 public:
  /**
   * @brief Default constructor.
   */
  MultiPersonality();

  /**
   * @brief Destructor.
   *
   * Responsible for deleting the managed current behavior object.
   */
  ~MultiPersonality() override;

  /**
   * @brief Copy constructor.
   *
   * Performs a deep copy of the currently active behavior using its clone
   * method.
   *
   * @param other The MultiPersonality object to copy from.
   */
  MultiPersonality(const MultiPersonality& other) {
    if (other.m_currentBehavior) {
      // Deep copy the underlying behavior
      m_currentBehavior = other.m_currentBehavior->clone();
    } else {
      m_currentBehavior = nullptr;
    }
    m_lastChange = other.m_lastChange;
  }

  /**
   * @brief Creates a deep copy (clone) of the behavior object.
   * @return IBehavior* A pointer to the new MultiPersonality object.
   */
  IBehavior* clone() const override { return new MultiPersonality(*this); }

  /**
   * @brief Calculates the steering force/direction based on the current active
   * behavior.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated steering adjustment.
   */
  double steer(IBestiole& currentBestiole,
               std::vector<IBestiole*> otherBestioles) override;

  /**
   * @brief Calculates the speed based on the current active behavior.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated speed value.
   */
  double speed(IBestiole& currentBestiole,
               std::vector<IBestiole*> otherBestioles) override;

  /**
   * @brief Switches the current active behavior to a new random behavior.
   *
   * This method typically involves selecting a new IBehavior implementation and
   * updating the internal m_currentBehavior pointer.
   */
  void changeBehavior();

  /**
   * @brief Gets the name of this behavior.
   * @return std::string The name "MultiPersonality".
   */
  std::string getName() const override { return "MultiPersonality"; }

  /**
   * @brief Gets the color associated with the current active behavior.
   *
   * @return unsigned char* A pointer to the RGB color array of the active
   * behavior, or nullptr if no behavior is currently active.
   */
  unsigned char* getColor() const override {
    return m_currentBehavior ? m_currentBehavior->getColor() : nullptr;
  }
};

#endif  // MULTIPERSONALITY_H