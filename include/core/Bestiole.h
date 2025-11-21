#ifndef BESTIOLE_H
#define BESTIOLE_H

#include <memory>
#include <string>
#include <utility>
#include <vector>  // Added for vector use in IBestiole methods

#include "../interfaces/IBestiole.h"
#include "UImg.h"

// Forward declarations
class Environment;
class IBehavior;

/**
 * @class Bestiole
 * @brief Represents a single autonomous agent (organism) in the simulation.
 *
 * Implements the IBestiole interface, handling movement, drawing, perception,
 * and behavior via a Strategy pattern (`IBehavior`).
 */
class Bestiole : public IBestiole {
 private:
  // --- Static Constants (k prefix) ---
  static const double
      kAffSize;  // Affichage size (radius/dimension for drawing)
  static const double kMaxSpeed;   // Maximum movement speed
  static const double kViewLimit;  // Maximum visual range (distance)
  static const int
      kMaxLifeSpan;    // Maximum number of steps the bestiole can live
  static int kNextId;  // Counter for assigning unique identity

 private:
  // --- Dynamic State (m_ prefix) ---
  int m_identity;  // Unique identifier
  int m_x, m_y;    // Current integer coordinates
  double m_cumulativeX,
      m_cumulativeY;  // Fractional coordinate accumulation for smooth movement
  double m_orientation;  // Direction of movement (angle in radians)
  double m_speed;        // Current movement speed

  unsigned char* m_color;  // RGB color array for drawing

  double
      m_resistance;  // Survival chance against hazards/collisions (0.0 to 1.0)
  double m_opacity;  // Opacity/visibility factor (0.0 to 1.0)
  int m_lifeSpan;    // Remaining lifespan (steps)
  double m_cloneRate;  // Probability of cloning per step

  // String representation of the current behavior (for logging/debugging)
  std::string m_behaviorString;

  // The behavior strategy (unique ownership)
  std::unique_ptr<IBehavior> m_behavior;

 private:
  /**
   * @brief Calculates and updates the bestiole's position.
   *
   * Handles movement based on speed/orientation and boundary bouncing logic.
   *
   * @param xLimit The width limit of the environment (renamed from 'xLim').
   * @param yLimit The height limit of the environment (renamed from 'yLim').
   */
  void move(int xLimit, int yLimit);

 public:
  // Bestiole(void); // Default constructor commented out in original

  /**
   * @brief Copy constructor.
   *
   * Creates a deep copy of the state and clones the behavior strategy.
   * @param otherBestiole The Bestiole object to copy from (renamed from 'b').
   */
  Bestiole(const Bestiole& otherBestiole);

  /**
   * @brief Constructor using a unique pointer for the initial behavior.
   *
   * @param behavior A unique pointer to the initial IBehavior strategy (renamed
   * from 'b').
   */
  Bestiole(std::unique_ptr<IBehavior> behavior);

  /**
   * @brief Destructor.
   *
   * Cleans up dynamically allocated resources (e.g., `m_color`).
   * @param void No parameters.
   */
  ~Bestiole(void);

  // --- IBestiole Interface Methods ---

  void action(Environment& myEnvironment) override;
  void draw(UImg& support) override;
  void initCoords(int xLimit, int yLimit) override;

  IBestiole* clone() override;
  bool collision() override;
  void kill(int delay) override;
  void changeBehavior(std::unique_ptr<IBehavior> behavior) override;
  void setCloneRate(double newCloneRate) override;

  /**
   * @brief Sets a new orientation for the bestiole.
   * @param orientationAngle The new orientation angle (in radians) (renamed
   * from 'o').
   */
  void setOrientation(double orientationAngle) override;

  // --- Getters ---
  int getX() const override;
  int getY() const override;
  double getOrientation() const override;
  double getSpeed() const override;
  double getMaxSpeed() const override;
  double getResistance() const override;
  double getOpacity() const override;
  int getLifeSpan() const override;
  IBehavior* getBehavior() const override;
  std::string getBehaviorString() const override;

  /**
   * @brief Checks if this bestiole can visually perceive another bestiole.
   * @param otherBestiole The other IBestiole to check visibility against
   * (renamed from 'b').
   * @return true if visible, false otherwise.
   */
  bool canSee(const IBestiole& otherBestiole) const override;

  // --- Friend Operators ---
  friend bool operator==(const Bestiole& b1, const Bestiole& b2);
};

#endif  // BESTIOLE_H