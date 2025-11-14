# Bestioles Ecosystem Simulation

A C++ simulation of a virtual 2D ecosystem inhabited by "Bestioles." This project demonstrates core object-oriented programming (OOP) principles and the application of design patterns to create complex, extensible, and emergent behaviors. The ecosystem is visualized in real-time using the CImg library.

## Features

* **Real-time Visualization:** The `Aquarium` class uses the CImg library to render the `Environment` and all `Bestioles` in real-time.
* **Dynamic Behaviors:** Bestioles' movement and actions are controlled by swappable behaviors (e.g., `Fearful`, `Gregarious`), implementing the **Strategy Pattern**.
* **Extensible Bestioles:** The **Decorator Pattern** is used to dynamically add accessories (`Fin`, `Shell`) and sensors (`Ears`, `Eyes`) to Bestioles.
* **Clean Creation:** The **Factory Pattern** is used to abstract the creation process of new `Bestiole` instances.

## Tech Stack

* **C++ (11 or newer)**
* **CImg:** Used for all 2D graphics and window management.
* **make:** For building the project.

## Building and Running

### Prerequisites

Before you begin, you will need:
* A C++ compiler (like `g++` or `clang++`)
* `make`
* X11 to display the simulation, which you would get like that on Debian:
    ```bash
    sudo apt-get install libx11-dev
    ```

### Steps

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/AloisHasNeurons/BestiolesEcosystem.git
    cd BestiolesEcosystem
    ```

2.  **Build the project:**
    ```bash
    make
    ```

3.  **Run the simulation:**
    ```bash
    ./main
    ```

## Project Design

This project is built around key design patterns to ensure flexibility and separation of concerns.

### Class Diagram

[Placeholder]

### Key Interactions (Sequence Diagrams)

[Placeholder]

## Project Structure
```
.
├── include/
│   ├── accessories/  # Concrete IAcessory decorators (Fin, Shell)
│   ├── behaviors/    # Concrete IBehavior strategies (Fearful, Gregarious)
│   ├── core/         # Core classes (Aquarium, Bestiole, Environment)
│   ├── interfaces/   # All abstract interfaces (IBestiole, IBehavior, etc.)
│   └── patterns/     # General patterns (Decorator, Factory)
├── src/
│   ├── core/         # .cpp files for core classes
│   └── main.cpp      # Main executable entry point
├── build/            # Compiled objects and executable
└── Makefile          # Build script
```
