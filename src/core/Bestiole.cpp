#include "core/Bestiole.h"

#include <cmath>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <utility>
#include <vector>

#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"
#include "core/Environment.h"
#include "interfaces/IBehavior.h"

// Define static constants for the Bestiole class.
const double Bestiole::AFF_SIZE = 8.;
const double Bestiole::MAX_SPEED = 10.;
const double Bestiole::VIEW_LIMIT = 30.;
const int Bestiole::MAX_LIFE_SPAN = 1000;

// Static counter to ensure each Bestiole has a unique identity.
int Bestiole::next = 0;

/**
 * @brief Constructs a Bestiole with a specified behavior.
 *
 * Initializes the bestiole's unique identity, randomizes its physical
 * characteristics (orientation, speed, lifespan, resistance, opacity, and
 * clone rate), and sets its color based on its initial behavior.
 *
 * @param b A unique pointer to the IBehavior strategy the bestiole will use.
 */
Bestiole::Bestiole(std::unique_ptr<IBehavior> b) : behavior(std::move(b)) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") with behavior" << std::endl;

  x = y = 0;
  cumulativeX = cumulativeY = 0.;
  // Random orientation between 0 and $2\pi$.
  orientation = static_cast<double>(rand()) / RAND_MAX * 2. * M_PI;
  // Random initial speed up to MAX_SPEED.
  speed = static_cast<double>(rand()) / RAND_MAX * MAX_SPEED;

  // Random lifespan up to MAX_LIFE_SPAN.
  lifeSpan =
      static_cast<int>(static_cast<double>(rand()) / RAND_MAX * MAX_LIFE_SPAN);
  // Random survival resistance factor between 0.0 and 1.0.
  resistance = static_cast<double>(rand()) / RAND_MAX;
  // Random opacity factor between 0.0 and 1.0.
  opacity = static_cast<double>(rand()) / RAND_MAX;
  // Random clone rate (probability of cloning per step).
  cloneRate = (static_cast<double>(rand()) / RAND_MAX) / 1000.0;

  color = new unsigned char[3];
  unsigned char* behaviorColor = behavior->getColor();

  // Set color based on the associated behavior, if available.
  if (behaviorColor != nullptr) {
    // Copy the values from the behavior's color attribute
    color[0] = behaviorColor[0];
    color[1] = behaviorColor[1];
    color[2] = behaviorColor[2];
  } else {
    // Fallback: Generate a random color if the behavior returns nullptr
    color[0] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    color[1] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
    color[2] = static_cast<int>(static_cast<double>(rand()) / RAND_MAX * 230.);
  }
}

/**
 * @brief Copy constructor for Bestiole.
 *
 * Creates a new Bestiole instance by copying the state of an existing one.
 * The new instance receives a unique identity and copies position, orientation,
 * speed, lifespan, resistance, opacity, clone rate, and color. The behavior
 * is currently reset due to implementation constraints.
 *
 * @param b The Bestiole object to copy from.
 */
// Copy constructor
Bestiole::Bestiole(const Bestiole& b) {
  identity = ++next;

  std::cout << "const Bestiole (" << identity << ") by copy" << std::endl;

  x = b.x;
  y = b.y;
  cumulativeX = cumulativeY = 0.;
  orientation = b.orientation;
  speed = b.speed;
  lifeSpan = b.lifeSpan;
  resistance = b.resistance;
  opacity = b.opacity;
  cloneRate = b.cloneRate;

  color = new unsigned char[3];
  // Copy the color array data.
  memcpy(color, b.color, 3 * sizeof(unsigned char));

  // Clone the behavior if it exists; otherwise, set to nullptr.
  if (b.behavior) {
    behavior = std::unique_ptr<IBehavior>(b.behavior->clone());
  } else {
    behavior = nullptr;
  }
}

/**
 * @brief Destroys the Bestiole object.
 *
 * Deletes the dynamically allocated color array.
 * @param void No parameters.
 */
Bestiole::~Bestiole(void) {
  delete[] color;

  std::cout << "dest Bestiole" << std::endl;
}

/**
 * @brief Initializes the bestiole's coordinates randomly within the given
 * limits.
 *
 * @param xLim The maximum x-coordinate (width of the environment).
 * @param yLim The maximum y-coordinate (height of the environment).
 */
void Bestiole::initCoords(int xLim, int yLim) {
  x = rand() % xLim;
  y = rand() % yLim;
}

/**
 * @brief Updates the bestiole's position based on its current speed and
 * orientation.
 *
 * Handles movement and boundary checks, reflecting the bestiole's orientation
 * if it hits the environment limits (bouncing off walls).
 *
 * @param xLim The width limit of the environment.
 * @param yLim The height limit of the environment.
 */
void Bestiole::move(int xLim, int yLim) {
  double nx, ny;
  // Calculate movement components for x and y.
  double dx = cos(orientation) * speed;
  double dy = -sin(orientation) * speed;
  int cx, cy;

  // Handle fractional movement using cumulative components.
  cx = static_cast<int>(cumulativeX);
  cumulativeX -= cx;
  cy = static_cast<int>(cumulativeY);
  cumulativeY -= cy;

  nx = x + dx + cx;
  ny = y + dy + cy;

  // Boundary check and bounce for the x-axis.
  if ((nx < 0) || (nx > xLim - 1)) {
    // Reverse orientation horizontally ($180 - \theta$).
    orientation = M_PI - orientation;
    cumulativeX = 0.;
  } else {
    x = static_cast<int>(nx);
    cumulativeX += nx - x;
  }

  // Boundary check and bounce for the y-axis.
  if ((ny < 0) || (ny > yLim - 1)) {
    // Reverse orientation vertically ($-\theta$).
    orientation = -orientation;
    cumulativeY = 0.;
  } else {
    y = static_cast<int>(ny);
    cumulativeY += ny - y;
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
  if (lifeSpan > 0) {
    lifeSpan--;
    if (lifeSpan == 0) {
      this->kill(0);
    }
  }

  // If the bestiole is dead or dying, skip action.
  if (lifeSpan <= 0) {
    return;
  }

  // Choose a random hazard level between 0 and 1
  double hazard = static_cast<double>(std::rand()) / RAND_MAX;

  // Compare hazard with cloneRate to determine if the bestiole is going to be
  // cloned If hazard is less than cloneRate, the bestiole is cloned
  if (hazard < cloneRate) {
    // Create a clone and add it to the environment.
    IBestiole* newBestiole = this->clone();
    myEnvironment.addMember(newBestiole);
  }

  // Apply behavior-based steering and speed adjustments.
  if (behavior) {
    // Get the list of all bestioles (potential neighbors) from the environment.
    std::vector<IBestiole*> neighbors = myEnvironment.getBestiolesList();
    // Pass the list to the behavior to calculate new orientation and speed.
    orientation = this->behavior->steer(*this, neighbors);
    speed = this->behavior->speed(*this, neighbors);
  }

  // Enforce speed limits.
  if (speed > MAX_SPEED) {
    speed = MAX_SPEED;
  } else if (speed < 0.) {
    speed = 0.;
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
  // Only draw if the bestiole is alive.
  if (lifeSpan < 0) {
    return;
  }
  // Use the behavior's color if available, otherwise use the bestiole's
  // default.
  unsigned char* drawColor = this->color;
  if (behavior && behavior->getColor()) {
    drawColor = behavior->getColor();
  }
  // Calculate head position (small offset in the direction of orientation).
  double xt = x + cos(orientation) * AFF_SIZE / 2.1;
  double yt = y - sin(orientation) * AFF_SIZE / 2.1;

  // Draw the body (ellipse).
  support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                       -orientation / M_PI * 180., drawColor);
  // Draw the head (circle).
  support.draw_circle(xt, yt, AFF_SIZE / 2., drawColor);
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
  return (b1.identity == b2.identity);
}

/**
 * @brief Checks if this bestiole can visually perceive another bestiole.
 *
 * Perception is based purely on the distance between the two bestioles,
 * constrained by the static VIEW_LIMIT.
 *
 * @param b The other IBestiole to check visibility against.
 * @return true if the other bestiole is within the VIEW_LIMIT, false otherwise.
 */
bool Bestiole::canSee(const IBestiole& b) const {
  // Dead bestioles cannot see.
  if (lifeSpan < 0) {
    return false;
  }

  double dist;
  // Calculate Euclidean distance.
  dist = std::sqrt((x - b.getX()) * (x - b.getX()) +
                   (y - b.getY()) * (y - b.getY()));
  // Check if distance is within the viewing limit.
  return (dist <= VIEW_LIMIT);
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
  std::cout << "Cloning Bestiole (" << identity << ")" << std::endl;
  return new Bestiole(*this);
}

/**
 * @brief Handles the consequence of a collision event.
 *
 * The bestiole has a chance to survive based on its `resistance` value. If it
 * survives, it reverses its orientation. If it fails the resistance check,
 * it is killed.
 *
 * @return true if the bestiole died from the collision, false otherwise (it
 * survived).
 */
bool Bestiole::collision() {
  // We can keep the random factor (survival chance) OR make it deterministic.
  // Current: "If I crash, I roll a die to see if my resistance saves me"

  // Random value for survival check.
  double hazard = static_cast<double>(std::rand()) / RAND_MAX;

  if (hazard > resistance) {
    kill(0);      // Die immediately
    return true;  // "I died"
  }

  // If they survive, usually they should bounce or change direction
  // Reverse orientation (bounce).
  orientation = orientation + M_PI;

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
    lifeSpan = -1;
  } else {
    lifeSpan = delay;
  }
}

/**
 * @brief Changes the bestiole's current behavior strategy.
 *
 * The unique pointer ensures the old behavior object is properly deleted.
 *
 * @param behavior A unique pointer to the new IBehavior strategy.
 */
void Bestiole::changeBehavior(std::unique_ptr<IBehavior> behavior) {
  if (!behavior) {
    return;
  }

  this->behavior = std::move(behavior);
  // [Temporary Fix] getName() is not in IBehavior. Using placeholder.
  this->behaviorString = "Unknown";
}

// --- Accessors and Mutators ---

/**
 * @brief Sets a new cloning rate for the bestiole.
 * @param newCloneRate The new probability of cloning per step.
 */
void Bestiole::setCloneRate(double newCloneRate) { cloneRate = newCloneRate; }

/**
 * @brief Sets a new orientation for the bestiole.
 * @param o The new orientation angle (in radians).
 */
void Bestiole::setOrientation(double o) { orientation = o; }

/**
 * @brief Gets the bestiole's current X coordinate.
 * @return The X coordinate.
 */
int Bestiole::getX() const { return x; }

/**
 * @brief Gets the bestiole's current Y coordinate.
 * @return The Y coordinate.
 */
int Bestiole::getY() const { return y; }

/**
 * @brief Gets the bestiole's current orientation.
 * @return The orientation angle (in radians).
 */
double Bestiole::getOrientation() const { return orientation; }

/**
 * @brief Gets the bestiole's current speed.
 * @return The current speed value.
 */
double Bestiole::getSpeed() const { return speed; }

/**
 * @brief Gets the maximum possible speed for this bestiole type.
 * @return The maximum speed (MAX_SPEED).
 */
double Bestiole::getMaxSpeed() const { return MAX_SPEED; }

/**
 * @brief Gets the bestiole's survival resistance value.
 * @return The resistance factor (0.0 to 1.0).
 */
double Bestiole::getResistance() const { return resistance; }

/**
 * @brief Gets the bestiole's opacity value.
 * @return The opacity factor (0.0 to 1.0).
 */
double Bestiole::getOpacity() const { return opacity; }

/**
 * @brief Gets the bestiole's remaining lifespan.
 * @return The remaining lifespan (in steps).
 */
int Bestiole::getLifeSpan() const { return lifeSpan; }

/**
 * @brief Gets a pointer to the bestiole's current behavior strategy.
 * @return A raw pointer to the IBehavior object.
 */
IBehavior* Bestiole::getBehavior() const { return behavior.get(); }

/**
 * @brief Gets the string representation of the bestiole's behavior.
 * @return The behavior name string.
 */
std::string Bestiole::getBehaviorString() const { return behaviorString; }