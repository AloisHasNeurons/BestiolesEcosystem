# Bestioles Ecosystem Simulation

A C++ simulation of a virtual 2D ecosystem inhabited by "Bestioles." This project demonstrates core object-oriented programming (OOP) principles and the application of design patterns to create complex, extensible, and emergent behaviors. The ecosystem is visualized in real-time using the CImg library.

## Features

* **Real-time Visualization:** The `Aquarium` class uses the CImg library to render the `Environment` and all `Bestioles` in real-time.
* **Dynamic Behaviors:** Bestioles' movement and actions are controlled by swappable behaviors (e.g., `Fearful`, `Gregarious`), implementing the **Strategy Pattern**.
* **Extensible Bestioles:** The **Decorator Pattern** is used to dynamically add accessories (`Fin`, `Shell`, `Camouflage`) and sensors (`Ears`, `Eyes`) to Bestioles.
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

### Strategy Pattern (Behaviors)

**Why this pattern?**
The Strategy Pattern was chosen to encapsulate the different movement and decision-making algorithms for Bestioles. This allows each Bestiole to have interchangeable behaviors without modifying its core implementation.

**How it's adapted:**
- The `IBehavior` interface defines two key methods: `steer()` for direction control and `speed()` for velocity management.
- Concrete behaviors (`Fearful`, `Gregarious`, `Kamikaze`, `Anticipating`, `MultiPersonality`) implement these methods with their own logic.
- Each Bestiole holds a `std::unique_ptr<IBehavior>`, allowing behaviors to be changed at runtime via `changeBehavior()`.
- Behaviors also define their own color representation, making visual distinction easy.
- The `MultiPersonality` behavior is a composite that switches between other behaviors periodically, demonstrating how strategies can be composed.

### Decorator Pattern (Accessories & Sensors)

**Why this pattern?**
The Decorator Pattern enables dynamic addition of capabilities (accessories and sensors) to Bestioles without subclassing. This keeps the class hierarchy flat while allowing rich combinations of features.

**How it's adapted:**
- The `Decorator` base class wraps an `IBestiole*` and delegates all interface calls to the wrapped object.
- Accessories (`Fin`, `Shell`, `Camouflage`) modify physical attributes like speed, resistance, and opacity.
- Sensors (`Eyes`, `Ears`) extend perception capabilities with different detection characteristics.
- Decorators can be stacked, allowing a Bestiole to have multiple accessories and sensors simultaneously.
- Each decorator overrides the `clone()` method to ensure proper deep copying of the entire decoration chain.

### Factory Pattern (Creation)

**Why this pattern?**
The Factory Pattern centralizes Bestiole creation logic, allowing the system to create diverse creatures based on configurable probability distributions without coupling the creation code to specific types.

**How it's adapted:**
- `IFactory` defines the creation interface with a single `createBestiole()` method.
- The `Factory` class accesses the `Environment` to retrieve behavior distribution probabilities.
- Using `std::discrete_distribution`, the factory performs weighted random selection of behavior types.
- The factory creates Bestioles with their initial behavior, abstracting creation details from the Environment.
- This design allows easy modification of population dynamics by adjusting distribution weights.

### Class Diagram

```mermaid
classDiagram
    direction TB

    %% Interfaces
    class IsKillable {
        <<interface>>
        +kill(delay: int)*
    }

    class IBestiole {
        <<interface>>
        +action(environment: Environment&)*
        +draw(img: UImg&)*
        +initCoords(x: int, y: int)*
        +clone(): IBestiole*
        +collision(): bool*
        +canSee(b: IBestiole&): bool*
        +changeBehavior(behavior: unique_ptr~IBehavior~)*
        +getX(): int*
        +getY(): int*
        +getOrientation(): double*
        +getSpeed(): double*
    }

    class IBehavior {
        <<interface>>
        +steer(b: IBestiole&, list: vector~IBestiole*~): double*
        +speed(b: IBestiole&, list: vector~IBestiole*~): double*
        +clone(): IBehavior*
        +getName(): string*
        +getColor(): unsigned char*
    }

    class IAccessory {
        <<interface>>
        +updateParameters()*
        +draw()*
    }

    class ISensor {
        <<interface>>
        +Detect(b: IBestiole&): bool*
        +draw()*
    }

    class IFactory {
        <<interface>>
        +createBestiole(): IBestiole*
    }

    %% Core Classes
    class Bestiole {
        -m_identity: int
        -m_x, m_y: int
        -m_orientation: double
        -m_speed: double
        -m_behavior: unique_ptr~IBehavior~
        -m_lifeSpan: int
        +action(environment: Environment&)
        +draw(img: UImg&)
        +clone(): IBestiole*
    }

    class Decorator {
        #m_bestiole: IBestiole*
        +action(environment: Environment&)
        +draw(img: UImg&)
        +clone(): IBestiole*
    }

    class Environment {
        -m_factory: IFactory&
        -m_bestiolesList: vector~IBestiole*~
        -m_behaviorDistribution: map~string, double~
        +step()
        +addMember(bestiole: IBestiole*)
        +getBehaviorDistribution(): vector~double~
    }

    class Aquarium {
        -m_population: Environment*
        -m_factory: Factory*
        -m_delayMs: int
        +run()
        +getEnvironment(): Environment&
    }

    class Factory {
        -env: Environment*
        +createBestiole(): IBestiole*
        +setEnvironment(env: Environment*)
    }

    %% Concrete Behaviors
    class Fearful {
        -m_maxNeighbors: int
        +steer(): double
        +speed(): double
    }
    class Gregarious {
        +steer(): double
        +speed(): double
    }
    class Kamikaze {
        +steer(): double
        +speed(): double
    }
    class Anticipating {
        +steer(): double
        +speed(): double
    }
    class MultiPersonality {
        -m_currentBehavior: IBehavior*
        +steer(): double
        +speed(): double
        +changeBehavior()
    }

    %% Concrete Accessories
    class Fin {
        -nu: double
    }
    class Shell {
        -omega: double
        -teta: double
    }
    class Camouflage {
        -psi: double
    }

    %% Concrete Sensors
    class Eyes {
        -delta: double
        -alpha: double
        -gamma: double
    }
    class Ears {
        -delta: double
        -gamma: double
    }

    %% Inheritance relationships
    IsKillable <|-- IBestiole
    IBestiole <|.. Bestiole
    IBestiole <|.. Decorator
    IBehavior <|.. Fearful
    IBehavior <|.. Gregarious
    IBehavior <|.. Kamikaze
    IBehavior <|.. Anticipating
    IBehavior <|.. MultiPersonality
    IAccessory <|.. Fin
    IAccessory <|.. Shell
    IAccessory <|.. Camouflage
    ISensor <|.. Eyes
    ISensor <|.. Ears
    IFactory <|.. Factory

    %% Composition/Association
    Bestiole --> IBehavior : has
    Decorator --> IBestiole : wraps
    Environment --> IBestiole : manages
    Environment --> IFactory : uses
    Aquarium --> Environment : contains
    Aquarium --> Factory : owns
    Factory --> Environment : references
    MultiPersonality --> IBehavior : delegates to
```

### Key Interactions (Sequence Diagrams)

#### Simulation Step

This diagram shows how a single simulation step is executed, demonstrating the interaction between the Aquarium, Environment, and Bestioles.

```mermaid
sequenceDiagram
    participant A as Aquarium
    participant E as Environment
    participant B as Bestiole
    participant Bh as IBehavior
    participant F as Factory

    A->>E: step()
    
    loop For each Bestiole
        E->>B: action(environment)
        B->>Bh: steer(self, otherBestioles)
        Bh-->>B: new orientation
        B->>Bh: speed(self, otherBestioles)
        Bh-->>B: new speed
        B->>B: move(xLimit, yLimit)
        B->>B: collision()
        alt Collision detected
            B->>B: kill(delay)
        end
    end
    
    E->>E: Remove dead Bestioles
    
    alt Birth probability met
        E->>F: createBestiole()
        F->>E: getBehaviorDistribution()
        E-->>F: probabilities
        F->>F: Select behavior (weighted random)
        F->>B: new Bestiole(behavior)
        F-->>E: new Bestiole*
        E->>E: addMember(bestiole)
    end
    
    E->>E: Add pending Bestioles
    
    loop For each Bestiole
        E->>B: draw(support)
    end
```

#### Bestiole Creation with Factory

This diagram illustrates how the Factory creates a new Bestiole with a randomly selected behavior.

```mermaid
sequenceDiagram
    participant E as Environment
    participant F as Factory
    participant D as discrete_distribution
    participant B as Bestiole
    participant Bh as Concrete Behavior

    E->>F: createBestiole()
    F->>E: getBehaviorDistribution()
    E-->>F: [0.2, 0.1, 0.3, 0.25, 0.15]
    
    F->>D: Create distribution(probabilities)
    F->>D: Generate random choice
    D-->>F: choice index (e.g., 2 for Gregarious)
    
    F->>Bh: new ConcreteB behavior()
    F->>B: new Bestiole(unique_ptr~IBehavior~)
    B->>B: Initialize position, speed, etc.
    F-->>E: Bestiole*
```

## Project Structure
```
.
├── Makefile              # Build script
├── README.md             # Project documentation
├── docs/                 # Project documentation files
│   ├── BE.pdf
│   └── Grille_Evaluation_BE_bestioles.pdf
├── include/
│   ├── CImg.h            # CImg library header
│   ├── UImg.h            # Custom image utility header
│   ├── accessories/      # Concrete IAccessory implementations
│   │   ├── Camouflage.h
│   │   ├── Fin.h
│   │   └── Shell.h
│   ├── behaviors/        # Concrete IBehavior strategies
│   │   ├── Anticipating.h
│   │   ├── Fearful.h
│   │   ├── Gregarious.h
│   │   ├── Kamikaze.h
│   │   └── MultiPersonality.h
│   ├── core/             # Core simulation classes
│   │   ├── Aquarium.h
│   │   ├── Bestiole.h
│   │   └── Environment.h
│   ├── interfaces/       # Abstract interfaces
│   │   ├── IAccessory.h
│   │   ├── IBehavior.h
│   │   ├── IBestiole.h
│   │   ├── ISensor.h
│   │   └── IsKillable.h
│   ├── patterns/         # Design pattern base classes
│   │   ├── Decorateur.h
│   │   ├── Factory.h
│   │   └── IFactory.h
│   └── sensors/          # Concrete ISensor implementations
│       ├── Ears.h
│       └── Eyes.h
└── src/
    ├── behaviors/        # Behavior implementation files
    │   ├── Anticipating.cpp
    │   ├── Fearful.cpp
    │   ├── Gregarious.cpp
    │   ├── Kamikaze.cpp
    │   └── MultiPersonality.cpp
    ├── core/             # Core class implementation files
    │   ├── Aquarium.cpp
    │   ├── Bestiole.cpp
    │   └── Environment.cpp
    ├── main.cpp          # Main executable entry point
    └── patterns/         # Pattern implementation files
        └── Factory.cpp
```
