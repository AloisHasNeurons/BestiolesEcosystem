#ifndef GREGARIOUS_H
#define GREGARIOUS_H

#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

// Forward declaration of the interface class
class IBestiole;

/**
 * @class Gregarious
 * @brief Implements the Gregarious behavior, characterized by an attraction
 * to other bestioles.
 */
class Gregarious : public IBehavior {
 private:
  unsigned char* m_color = new unsigned char[3]{
      0, 255, 0};  // Green color (R:0, G:255, B:0) for Gregarious bestioles
 public:
  /**
   * @brief Calculates the steering force/direction for the Gregarious bestiole.
   *
   * Steering aims to keep the bestiole near others.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated steering adjustment (e.g., angle change).
   */
  double steer(IBestiole* currentBestiole,
               std::vector<IBestiole*> otherBestioles) override;

  /**
   * @brief Calculates the speed for the Gregarious bestiole.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated speed value.
   */
  double speed(IBestiole* currentBestiole,
               std::vector<IBestiole*> otherBestioles) override;

  /**
   * @brief Default constructor.
   */
  Gregarious() {}

  /**
   * @brief Copy constructor.
   *
   * Performs a shallow copy of the color pointer.
   *
   * @param other The Gregarious object to copy from.
   */
  Gregarious(const Gregarious& other) { m_color = other.m_color; }

  /**
   * @brief Creates a deep copy (clone) of the behavior object.
   * @return IBehavior* A pointer to the new Gregarious object.
   */
  IBehavior* clone() const override { return new Gregarious(*this); }

  /**
   * @brief Gets the name of this behavior.
   * @return std::string The name "Gregarious".
   */
  std::string getName() const override { return "Gregarious"; }

  /**
   * @brief Gets the color associated with this behavior.
   * @return unsigned char* A pointer to the RGB color array.
   */
  unsigned char* getColor() const override { return m_color; }
};

#endif  // GREGARIOUS_H