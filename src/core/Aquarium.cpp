#include "core/Aquarium.h"

#include <iostream>
#include <utility>

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
 * @param kWidth The width of the simulation area (in pixels).
 * @param kHeight The height of the simulation area (in pixels).
 * @param kDelayMs The delay (in milliseconds) between each simulation step
 * (renamed from '_delay').
 */
Aquarium::Aquarium(int kWidth, int kHeight, int kDelayMs)
    // Initialize CImgDisplay and the private delay member.
    : CImgDisplay(), m_delayMs(kDelayMs) {
  // Define screen dimensions for positioning (these are constants, often
  // defined globally or derived).
  const int kScreenWidth = 1280;
  const int kScreenHeight = 1024;

  // std::cout << "const Aquarium" << std::endl;

  // Create the factory and the environment.
  m_factory = new Factory();
  m_population = new Environment(kWidth, kHeight, *m_factory);
  // Link the environment back to the factory so the factory knows the
  // environment bounds.
  m_factory->setEnvironment(m_population);

  // Set the display image and title, and move the window to the center of the
  // screen.
  assign(*m_population, "Ecosystem Simulation");
  // Calculate center position to move the window.
  move(static_cast<int>((kScreenWidth - kWidth) / 2),
       static_cast<int>((kScreenHeight - kHeight) / 2));
}

/**
 * @brief Destroys the Aquarium object.
 *
 * Cleans up and deletes the dynamically allocated Environment and Factory
 * objects to prevent memory leaks.
 * @param void No parameters.
 */
Aquarium::~Aquarium(void) {
  // Free memory allocated for population and factory.
  delete m_population;
  delete m_factory;

  // std::cout << "dest Aquarium" << std::endl;
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
  // std::cout << "running Aquarium" << std::endl;

  // Main simulation loop: continues as long as the CImgDisplay window is open.
  while (!is_closed()) {
    // Check for user keyboard input.
    if (is_key()) {
      // std::cout << "You pressed key " << static_cast<unsigned char>(key())
      //           << " (" << key() << ")" << std::endl;
      // Close the window if the ESC key is pressed.
      if (is_keyESC()) close();
    }

    // Advance the simulation by one step.
    m_population->step();
    // Refresh the display with the updated environment state.
    display(*m_population);
    // Pause for the set delay time (m_delayMs milliseconds).
    wait(m_delayMs);
  }
}