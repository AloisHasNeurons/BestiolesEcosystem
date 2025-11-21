#include "core/Aquarium.h"

#include <iostream>

#include "core/Environment.h"
#include "patterns/Factory.h"

/**
 * @brief Constructs an Aquarium object, initializing the simulation environment
 * and display.
 *
 * Initializes the CImgDisplay, creates the simulation Environment and the
 * Factory used to generate members. It centers the display window on the
 * screen.
 *
 * @param width The width of the simulation area (in pixels).
 * @param height The height of the simulation area (in pixels).
 * @param _delay The delay (in milliseconds) between each simulation step.
 */
Aquarium::Aquarium(int width, int height, int _delay)
    : CImgDisplay(), delay(_delay) {
  // Define screen dimensions for positioning.
  int screenWidth = 1280;
  int screenHeight = 1024;

  std::cout << "const Aquarium" << std::endl;

  // Create the factory and the environment.
  factory = new Factory();
  population = new Environment(width, height, *factory);
  // Link the environment back to the factory.
  factory->setEnvironment(population);

  // Set the display image and title, and move the window to the center of the
  // screen.
  assign(*population, "Ecosystem Simulation");
  move(static_cast<int>((screenWidth - width) / 2),
       static_cast<int>((screenHeight - height) / 2));
}

/**
 * @brief Destroys the Aquarium object.
 *
 * Cleans up and deletes the dynamically allocated Environment and Factory
 * objects.
 * @param void No parameters.
 */
Aquarium::~Aquarium(void) {
  // Free memory allocated for population and factory.
  delete population;
  delete factory;

  std::cout << "dest Aquarium" << std::endl;
}

/**
 * @brief Starts and runs the main simulation loop.
 *
 * The loop continues until the display window is closed. It handles user input
 * (like the ESC key), updates the environment one step at a time, displays the
 * updated environment, and waits for the specified delay.
 * @param void No parameters.
 */
void Aquarium::run(void) {
  std::cout << "running Aquarium" << std::endl;

  // Main simulation loop.
  while (!is_closed()) {
    // Check for user keyboard input.
    if (is_key()) {
      std::cout << "You pressed key " << static_cast<unsigned char>(key())
                << " (" << key() << ")" << std::endl;
      // Close the window if the ESC key is pressed.
      if (is_keyESC()) close();
    }

    // Advance the simulation by one step.
    population->step();
    // Refresh the display with the updated environment state.
    display(*population);
    // Pause for the set delay time.
    wait(delay);
  }
}