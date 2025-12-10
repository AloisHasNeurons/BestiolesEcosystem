# UML Diagrams

This directory contains detailed UML sequence diagrams for the Bestioles Ecosystem simulation.

## Diagrams

### [Bestiole Creation with Factory](factory-creation.md)
Illustrates the complete process of creating a new Bestiole using the Factory pattern, including:
- Weighted random selection of behaviors based on environment distribution
- Sequential application of decorators (Eyes, Ears, Camouflage, Fin, Shell)
- Interaction between Factory and Environment for configuration

### [Bestiole Collision](collision.md)
Shows the collision detection mechanism and survival determination:
- Distance-based collision detection
- Resistance and armor factor calculation
- Survival probability based on random check
- Collision outcome (death or bounce)

### [Bestiole Action and Sensor Interaction](action-method.md)
Details the `action` method execution flow, focusing on sensor-based perception:
- Lifespan management and cloning
- Steering behavior with sensor integration
- How `canSee` and `canHear` methods work with Eyes and Ears decorators
- Distance, field-of-view, and camouflage checks
- Speed calculation and movement

## Main Diagrams

The main class diagram and simulation step sequence diagram can be found in the [README.md](../../README.md) file at the root of the repository.
