#ifndef SIMULATION_CONFIG_H
#define SIMULATION_CONFIG_H

#include <map>
#include <string>

struct SimulationConfig {
    int width = 640;
    int height = 480;
    int delay = 30;
    double maxSpeed = 10.0;
    double minSpeed = 2.0;

    std::map<std::string, int> initialPopulation = {
        {"Gregarious", 5}, {"Fearful", 5}, {"Kamikaze", 5},
        {"Anticipating", 5}, {"MultiPersonality", 5}
    };

    std::map<std::string, double> spawnProbabilities = {
        {"Gregarious", 0.3}, {"Fearful", 0.1}, {"Kamikaze", 0.25},
        {"Anticipating", 0.2}, {"MultiPersonality", 0.15}
    };

    std::map<std::string, double> accessories = {
        {"Eyes", 0.7}, {"Ears", 0.7}, {"Fins", 0.3},
        {"Shell", 0.15}, {"Camouflage", 0.2}
    };

    std::map<std::string, double> eyesparams = {
        {"minimum detection distance", 30.0},
        {"maximum detection distance", 100.0},
        {"minimum field-of-view angle", 90.0},
        {"maximum field-of-view angle", 270.0},
        {"lower bound of detection capability", 0.6},
        {"upper bound of detection capability", 1.0}
    };

    std::map<std::string, double> earsparams = {
        {"minimum detection distance", 20.0},
        {"maximum detection distance", 80.0},
        {"lower bound of detection capability", 0.6},
        {"upper bound of detection capability", 0.9}
    };

    std::map<std::string, double> accessoriesparams = {
        {"minimum speed factor for Fins", 1.0},
        {"maximum speed factor for Fins", 2.0},
        {"minimum speed reduction factor for Shell", 1.0},
        {"maximum speed reduction factor for Shell", 2.0},
        {"minimum armor enhancement factor for Shell", 1.0},
        {"maximum armor enhancement factor for Shell", 2.0},
        {"minimum camouflage value", 0.3},
        {"maximum camouflage value", 0.7}
    };
};

#endif // SIMULATION_CONFIG_H
