#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

// Forward declaration of Bestiole class
class Bestiole;

/**
 * @class Kamikaze
 * @brief Implements the Kamikaze predator behavior.
 *
 * This behavior pattern is characterized by high-risk actions, often resulting
 * in direct approach or aggressive pursuit of targets.
 */
class Kamikaze : public IBehavior {
 private:
  // Use a more descriptive name for the private color array, including 'm_'
  // prefix
  unsigned char* m_color = new unsigned char[3]{
      255, 0, 0};  // Red color for Kamikaze bestioles (R:255, G:0, B:0)

 public:
  /**
   * @brief Calculates the steering force/direction for the Kamikaze bestiole.
   *
   * The Kamikaze steering prioritizes direct movement toward nearby
   * bestioles.
   *
   * @param currentBestiole The bestiole applying this behavior (renamed from
   * 'b').
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated steering adjustment (e.g., angle change).
   */
  double steer(IBestiole* currentBestiole,
               std::vector<IBestiole*> otherBestioles) override;

  /**
   * @brief Calculates the speed for the Kamikaze bestiole.
   *
   * @param currentBestiole The bestiole applying this behavior (renamed from
   * 'b').
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated speed value.
   */
  double speed(IBestiole* currentBestiole,
               std::vector<IBestiole*> otherBestioles) override;

  /**
   * @brief Default constructor.
   */
  Kamikaze() {}

  /**
   * @brief Copy constructor.
   *
   * Shares the color pointer with the other Kamikaze object.
   * @param other The Kamikaze object to copy from.
   */
  Kamikaze(const Kamikaze& other) { m_color = other.m_color; }

  /**
   * @brief Creates a deep copy (clone) of the behavior object.
   * @return IBehavior* A pointer to the new Kamikaze object.
   */
  IBehavior* clone() const override { return new Kamikaze(*this); }

  /**
   * @brief Gets the name of this behavior.
   * @return std::string The name "Kamikaze".
   */
  std::string getName() const override { return "Kamikaze"; }

  /**
   * @brief Gets the color associated with this behavior.
   * @return unsigned char* A pointer to the RGB color array.
   */
  unsigned char* getColor() const override { return m_color; }
};

#endif  // KAMIKAZE_H