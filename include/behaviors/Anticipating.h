#ifndef ANTICIPATING_H
#define ANTICIPATING_H

#include <string> // Added <string> include
#include <vector>

#include "../interfaces/IBehavior.h"

// Forward declaration of the interface class
class IBestiole;

/**
 * @class Anticipating
 * @brief Implements the Anticipating behavior, characterized by predicting
 * future positions or movements of other bestioles for optimal steering.
 */
class Anticipating : public IBehavior {
private:
  unsigned char *m_color = new unsigned char[3]{
      255, 0,
      255}; // Magenta color (R:255, G:0, B:255) for Anticipating behavior
public:
  /**
   * @brief Calculates the steering force/direction for the Anticipating
   * bestiole.
   *
   * Steering involves projecting the motion of other bestioles forward in time.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated steering adjustment (e.g., angle change).
   */
  double steer(IBestiole *currentBestiole,
               std::vector<IBestiole *> otherBestioles) override;

  /**
   * @brief Calculates the speed for the Anticipating bestiole.
   *
   * Speed adjustments might be used to evade predicted paths.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated speed value.
   */
  double speed(IBestiole *currentBestiole,
               std::vector<IBestiole *> otherBestioles) override;

  /**
   * @brief Default constructor.
   */
  Anticipating() {}

  /**
   * @brief Copy constructor.
   *
   * Performs a shallow copy of the color pointer.
   *
   * @param other The Anticipating object to copy from.
   */
  Anticipating(const Anticipating &other) { m_color = other.m_color; }

  /**
   * @brief Creates a deep copy (clone) of the behavior object.
   * @return IBehavior* A pointer to the new Anticipating object.
   */
  IBehavior *clone() const override { return new Anticipating(*this); }

  /**
   * @brief Gets the name of this behavior.
   * @return std::string The name "Anticipating".
   */
  std::string getName() const override { return "Anticipating"; }

  /**
   * @brief Gets the color associated with this behavior.
   * @return unsigned char* A pointer to the RGB color array.
   */
  unsigned char *getColor() const override { return m_color; }
};

#endif // ANTICIPATING_H