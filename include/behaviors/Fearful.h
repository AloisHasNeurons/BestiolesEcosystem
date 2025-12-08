#ifndef FEARFUL_H
#define FEARFUL_H

#include <string>
#include <vector>

#include "../interfaces/IBehavior.h"

// Forward declaration of the interface class
class IBestiole;

/**
 * @class Fearful
 * @brief Implements the Fearful behavior, characterized by evasion and
 * maintenance of distance from other bestioles.
 */
class Fearful : public IBehavior {
private:
  // The maximum number of neighbors this bestiole tolerates before reacting.
  int m_maxNeighbors;
  unsigned char *m_color = new unsigned char[3]{
      0, 0, 255}; // Blue color (R:0, G:0, B:255) for Fearful behavior
public:
  /**
   * @brief Calculates the steering force/direction for the Fearful bestiole.
   *
   * Steering aims to increase distance from potential threats or close
   * neighbors.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated steering adjustment (e.g., angle change).
   */
  double steer(IBestiole *currentBestiole,
               std::vector<IBestiole *> otherBestioles) override;

  /**
   * @brief Calculates the speed for the Fearful bestiole.
   *
   * @param currentBestiole The bestiole applying this behavior.
   * @param otherBestioles A list of all other bestioles in the environment.
   * @return double The calculated speed value.
   */
  double speed(IBestiole *currentBestiole,
               std::vector<IBestiole *> otherBestioles) override;

  /**
   * @brief Constructor.
   * @param max_neighbors The maximum number of neighbors allowed (defaults to
   * 1).
   */
  explicit Fearful(int max_neighbors = 1) : m_maxNeighbors(max_neighbors) {}

  /**
   * @brief Copy constructor.
   *
   * Copies the maximum neighbors limit and performs a shallow copy of the color
   * pointer.
   *
   * @param other The Fearful object to copy from.
   */
  Fearful(const Fearful &other) {
    m_maxNeighbors = other.m_maxNeighbors;
    m_color = other.m_color;
  }

  /**
   * @brief Creates a deep copy (clone) of the behavior object.
   * @return IBehavior* A pointer to the new Fearful object.
   */
  IBehavior *clone() const override { return new Fearful(*this); }

  /**
   * @brief Gets the name of this behavior.
   * @return std::string The name "Fearful".
   */
  std::string getName() const override { return "Fearful"; }

  /**
   * @brief Gets the color associated with this behavior.
   * @return unsigned char* A pointer to the RGB color array.
   */
  unsigned char *getColor() const override { return m_color; }
};

#endif // FEARFUL_H