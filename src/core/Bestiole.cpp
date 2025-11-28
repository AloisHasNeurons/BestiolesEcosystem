#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"
#include "core/Environment.h"
#include "interfaces/IBehavior.h"

// Define static constants for the Bestiole class (using 'k' prefix).
const double Bestiole::kAffSize = 8.;
const double Bestiole::kMaxSpeed = 10.;
const double Bestiole::kViewLimit = 30.;
const int Bestiole::kMaxLifeSpan = 1000;

// Static counter to ensure each Bestiole has a unique identity.
int Bestiole::kNextId = 0;

/**
 * @brief Constructs a Bestiole with a specified behavior.
 *
 * Initializes the bestiole's unique identity, randomizes its physical
 * characteristics (orientation, speed, lifespan, resistance, opacity, and
 * clone rate), and sets its color based on its initial behavior.
 *
 * @param behavior A unique pointer to the IBehavior strategy the bestiole will
 * use.
 */
Bestiole::Bestiole(std::unique_ptr<IBehavior> behavior)
    : m_behavior(std::move(behavior)) {
  m_identity = ++kNextId;

  // std::cout << "const Bestiole (" << m_identity << ") with behavior"
  //           << std::endl;

  if (m_behavior) {
    m_behaviorString = m_behavior->getName();
  } else {
    m_behaviorString = "Unknown";
  }

  m_x = m_y = 0;
  m_cumulativeX = m_cumulativeY = 0.;
  // Random orientation between 0 and $2\pi$.
  m_orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  // Random initial speed up to MAX_SPEED.
  m_speed = static_cast<double>(rand()) / RAND_MAX * kMaxSpeed;

  // Random lifespan up to MAX_LIFE_SPAN.
  m_lifeSpan =
      static_cast<int>(static_cast<double>(rand()) / RAND_MAX * kMaxLifeSpan);
  // Random survival resistance factor between 0.0 and 1.0.
  m_resistance = static_cast<double>(rand()) / RAND_MAX;
  // Random opacity factor between 0.0 and 1.0.
  m_opacity = static_cast<double>(rand()) / RAND_MAX;
  // Random clone rate (probability of cloning per step).
  m_cloneRate = (static_cast<double>(rand()) / RAND_MAX) / 1000.0;

  m_color = new unsigned char[3];
  unsigned char* behaviorColor = m_behavior->getColor();

  // Set color based on the associated behavior, if available.
  if (behaviorColor != nullptr) {
    // Copy the values from the behavior's color attribute
    m_color[0] = behaviorColor[0];
    m_color[1] = behaviorColor[1];
    m_color[2] = behaviorColor[2];
  } else {
    // Fallback: Generate a random color if the behavior returns nullptr
    m_color[0] =
        static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    m_color[1] =
        static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    m_color[2] =
        static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  }
}

/**
 * @brief Copy constructor for Bestiole.
 *
 * Creates a new Bestiole instance by copying the state of an existing one.
 * The new instance receives a unique identity and copies position, orientation,
 * speed, lifespan, resistance, opacity, clone rate, and color. The behavior
 * is cloned using the Strategy pattern's `clone` method.
 *
 * @param otherBestiole The Bestiole object to copy from (renamed from 'b').
 */
// Copy constructor
Bestiole::Bestiole(const Bestiole& otherBestiole) {
  m_identity = ++kNextId;

  // std::cout << "const Bestiole (" << m_identity << ") by copy" << std::endl;

  m_x = otherBestiole.m_x;
  m_y = otherBestiole.m_y;
  m_cumulativeX = m_cumulativeY =
      0.;  // Reset cumulative movement for a new clone
  m_orientation = otherBestiole.m_orientation;
  m_speed = otherBestiole.m_speed;
  m_lifeSpan = otherBestiole.m_lifeSpan;
  m_resistance = otherBestiole.m_resistance;
  m_opacity = otherBestiole.m_opacity;
  m_cloneRate = otherBestiole.m_cloneRate;

  m_color = new unsigned char[3];
  // Copy the color array data.
  memcpy(m_color, otherBestiole.m_color, 3 * sizeof(unsigned char));

  // Clone the behavior if it exists; otherwise, set to nullptr.
  if (otherBestiole.m_behavior) {
    // Perform a deep copy of the behavior object using the clone method.
    m_behavior = std::unique_ptr<IBehavior>(otherBestiole.m_behavior->clone());
    m_behaviorString = m_behavior->getName();
  } else {
    m_behavior = nullptr;
    m_behaviorString = "Unknown";
  }
}

/**
 * @brief Destroys the Bestiole object.
 *
 * Deletes the dynamically allocated color array to prevent memory leaks.
 * @param void No parameters.
 */
Bestiole::~Bestiole(void) {
  delete[] m_color;

  // std::cout << "dest Bestiole" << std::endl;
}

/**
 * @brief Initializes the bestiole's coordinates randomly within the given
 * limits.
 *
 * @param xLimit The maximum x-coordinate (width of the environment) (renamed
 * from 'xLim').
 * @param yLimit The maximum y-coordinate (height of the environment) (renamed
 * from 'yLim').
 */
void Bestiole::initCoords(int xLimit, int yLimit) {
  m_x = rand() % xLimit;
  m_y = rand() % yLimit;
}

/**
 * @brief Updates the bestiole's position based on its current speed and
 * orientation.
 *
 * Handles movement and boundary checks, reflecting the bestiole's orientation
 * if it hits the environment limits (bouncing off walls).
 *
 * @param xLimit The width limit of the environment (renamed from 'xLim').
 * @param yLimit The height limit of the environment (renamed from 'yLim').
 */
void Bestiole::move(int xLimit, int yLimit) {
  double newX, newY;
  // Calculate movement components for x and y.
  double dx = cos(m_orientation) * m_speed;
  double dy = -sin(m_orientation) * m_speed;
  int cumulativeXInt, cumulativeYInt;

  // Handle fractional movement using cumulative components.
  cumulativeXInt = static_cast<int>(m_cumulativeX);
  m_cumulativeX -= cumulativeXInt;
  cumulativeYInt = static_cast<int>(m_cumulativeY);
  m_cumulativeY -= cumulativeYInt;

  newX = m_x + dx + cumulativeXInt;
  newY = m_y + dy + cumulativeYInt;

  // Boundary check and bounce for the x-axis.
  if ((newX < 0) || (newX > xLimit - 1)) {
    // Reverse orientation horizontally (reflection across the y-axis: $\pi -
    // \theta$).
    m_orientation = M_PI - m_orientation;
    m_cumulativeX = 0.;
  } else {
    m_x = static_cast<int>(newX);
    m_cumulativeX += newX - m_x;
  }

  // Boundary check and bounce for the y-axis.
  if ((newY < 0) || (newY > yLimit - 1)) {
    // Reverse orientation vertically (reflection across the x-axis: $-\theta$).
    m_orientation = -m_orientation;
    m_cumulativeY = 0.;
  } else {
    m_y = static_cast<int>(newY);
    m_cumulativeY += newY - m_y;
  }
}

/**
 * @brief Executes the bestiole's action sequence for one time step.
 *
 * Decrements lifespan, checks for cloning probability, delegates steering
 * and speed calculation to the current behavior strategy, constrains speed,
 * and finally moves the bestiole.
 *
 * @param myEnvironment The environment in which the bestiole exists.
 */
void Bestiole::action(Environment& myEnvironment) {
  // Decrease lifespan and check if the bestiole should die of old age.
  if (m_lifeSpan > 0) {
    m_lifeSpan--;
    if (m_lifeSpan == 0) {
      this->kill(0);  // Mark for instant death
      myEnvironment.recordEvent("Natural death of " + getBehaviorString());
    }
  }

  // If the bestiole is dead or dying, skip action.
  if (m_lifeSpan <= 0) {
    return;
  }

  // Choose a random hazard level between 0 and 1
  double hazard = static_cast<double>(std::rand()) / RAND_MAX;

  // Compare hazard with m_cloneRate to determine if the bestiole is going to be
  // cloned.
  if (hazard < m_cloneRate) {
    // Create a clone and add it to the environment.
    IBestiole* newBestiole = this->clone();
    myEnvironment.addMember(newBestiole);
    myEnvironment.recordEvent("Clone of " + getBehaviorString());
  }

  // Apply behavior-based steering and speed adjustments.
  if (m_behavior) {
    // Get the list of all bestioles (potential neighbors) from the environment.
    std::vector<IBestiole*> neighbors = myEnvironment.getBestiolesList();
    // Pass the list to the behavior to calculate new orientation and speed.
    m_orientation = this->m_behavior->steer(*this, neighbors);
    m_speed = this->m_behavior->speed(*this, neighbors);
  }

  // Enforce speed limits.
  if (m_speed > kMaxSpeed) {
    m_speed = kMaxSpeed;
  } else if (m_speed < 0.) {
    m_speed = 0.;
  }

  // Move the bestiole within the environment bounds.
  move(myEnvironment.width(), myEnvironment.height());
}

/**
 * @brief Draws the bestiole on the provided image support.
 *
 * Draws an ellipse for the body and a circle for the head, with orientation
 * indicating direction.
 *
 * @param support The CImg object representing the environment/display surface.
 */
void Bestiole::draw(UImg& support) {
  // Only draw if the bestiole is alive (lifeSpan > 0).
  if (m_lifeSpan < 0) {
    return;
  }
  // Use the behavior's color if available, otherwise use the bestiole's
  // default (m_color).
  unsigned char* drawColor = this->m_color;
  if (m_behavior && m_behavior->getColor()) {
    drawColor = m_behavior->getColor();
  }
  // Calculate head position (small offset in the direction of orientation).
  double headX = m_x + cos(m_orientation) * kAffSize / 2.1;
  double headY = m_y - sin(m_orientation) * kAffSize / 2.1;

  // Draw the body (ellipse).
  support.draw_ellipse(m_x, m_y, kAffSize, kAffSize / 5.,
                       -m_orientation / M_PI * 180., drawColor);
  // Draw the head (circle).
  support.draw_circle(headX, headY, kAffSize / 2., drawColor);
}

/**
 * @brief Overloads the equality operator to compare two Bestiole objects.
 *
 * Two bestioles are considered equal if they share the same unique identity.
 *
 * @param b1 The first Bestiole.
 * @param b2 The second Bestiole.
 * @return true if both bestioles have the same identity, false otherwise.
 */
bool operator==(const Bestiole& b1, const Bestiole& b2) {
  return (b1.m_identity == b2.m_identity);
}

/**
 * @brief Checks if this bestiole can visually perceive another bestiole.
 *
 * Perception is based purely on the distance between the two bestioles,
 * constrained by the static VIEW_LIMIT.
 *
 * @param otherBestiole The other IBestiole to check visibility against (renamed
 * from 'b').
 * @return true if the other bestiole is within the kViewLimit, false otherwise.
 */
bool Bestiole::canSee(const IBestiole& otherBestiole) const {
  // Dead bestioles cannot see.
  if (m_lifeSpan < 0) {
    return false;
  }

  double dist;
  // Calculate Euclidean distance.
  dist = std::sqrt((m_x - otherBestiole.getX()) * (m_x - otherBestiole.getX()) +
                   (m_y - otherBestiole.getY()) * (m_y - otherBestiole.getY()));
  // Check if distance is within the viewing limit.
  return (dist <= kViewLimit);
}

/**
 * @brief Creates a deep copy (clone) of the current Bestiole.
 *
 * Uses the copy constructor to create a new, distinct Bestiole with identical
 * properties but a new identity.
 *
 * @return A pointer to the newly created Bestiole clone.
 */
IBestiole* Bestiole::clone() {
  // std::cout << "Cloning Bestiole (" << m_identity << ")" << std::endl;
  return new Bestiole(*this);
}

/**
 * @brief Handles the consequence of a collision event.
 *
 * The bestiole has a chance to survive based on its `m_resistance` value. If it
 * survives, it reverses its orientation. If it fails the resistance check,
 * it is killed.
 *
 * @return true if the bestiole died from the collision, false otherwise (it
 * survived).
 */
bool Bestiole::collision() {
  // Random value for survival check.
  double hazard = static_cast<double>(std::rand()) / RAND_MAX;

  if (hazard > m_resistance) {
    kill(0);      // Die immediately
    return true;  // "I died"
  }

  // If they survive, reverse orientation (bounce).
  // This logic ensures the orientation wraps correctly within $[-\pi, \pi]$ or
  // $[0, 2\pi]$
  if (m_orientation < M_PI) {
    m_orientation = m_orientation + M_PI;
  } else {
    m_orientation = m_orientation - M_PI;
  }

  return false;  // "I survived"
}

/**
 * @brief Marks the bestiole for death.
 *
 * Sets the lifespan to -1 (instant death) or a positive delay (time until
 * actual removal).
 *
 * @param delay The number of steps before the bestiole is fully removed (0 for
 * instant death).
 */
void Bestiole::kill(int delay) {
  if (delay <= 0) {
    m_lifeSpan =
        -1;  // Negative lifespan signals immediate removal in the next step
  } else {
    m_lifeSpan = delay;
  }
}

/**
 * @brief Changes the bestiole's current behavior strategy.
 *
 * The unique pointer ensures the old behavior object is properly deleted
 * when the unique_ptr goes out of scope or is reassigned.
 *
 * @param newBehavior A unique pointer to the new IBehavior strategy (renamed
 * from 'behavior').
 */
void Bestiole::changeBehavior(std::unique_ptr<IBehavior> newBehavior) {
  if (!newBehavior) {
    return;
  }

  this->m_behavior = std::move(newBehavior);
  this->m_behaviorString = this->m_behavior->getName();
}

// --- Accessors and Mutators ---

/**
 * @brief Sets a new cloning rate for the bestiole.
 * @param newCloneRate The new probability of cloning per step.
 */
void Bestiole::setCloneRate(double newCloneRate) { m_cloneRate = newCloneRate; }

/**
 * @brief Sets a new orientation for the bestiole.
 * @param orientationAngle The new orientation angle (in radians) (renamed from
 * 'o').
 */
void Bestiole::setOrientation(double orientationAngle) {
  m_orientation = orientationAngle;
}

/**
 * @brief Gets the bestiole's current X coordinate.
 * @return The X coordinate.
 */
int Bestiole::getX() const { return m_x; }

/**
 * @brief Gets the bestiole's current Y coordinate.
 * @return The Y coordinate.
 */
int Bestiole::getY() const { return m_y; }

/**
 * @brief Gets the bestiole's current orientation.
 * @return The orientation angle (in radians).
 */
double Bestiole::getOrientation() const { return m_orientation; }

/**
 * @brief Gets the bestiole's current speed.
 * @return The current speed value.
 */
double Bestiole::getSpeed() const { return m_speed; }

/**
 * @brief Gets the maximum possible speed for this bestiole type.
 * @return The maximum speed (kMaxSpeed).
 */
double Bestiole::getMaxSpeed() const { return kMaxSpeed; }

/**
 * @brief Gets the bestiole's survival resistance value.
 * @return The resistance factor (0.0 to 1.0).
 */
double Bestiole::getResistance() const { return m_resistance; }

/**
 * @brief Gets the bestiole's opacity value.
 * @return The opacity factor (0.0 to 1.0).
 */
double Bestiole::getOpacity() const { return m_opacity; }

/**
 * @brief Gets the bestiole's remaining lifespan.
 * @return The remaining lifespan (in steps).
 */
int Bestiole::getLifeSpan() const { return m_lifeSpan; }

/**
 * @brief Gets a pointer to the bestiole's current behavior strategy.
 * @return A raw pointer to the IBehavior object.
 */
IBehavior* Bestiole::getBehavior() const { return m_behavior.get(); }

/**
 * @brief Gets the string representation of the bestiole's behavior.
 * @return The behavior name string.
 */
std::string Bestiole::getBehaviorString() const { return m_behaviorString; }