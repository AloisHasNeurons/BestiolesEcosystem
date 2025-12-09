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
};

#endif // SIMULATION_CONFIG_H
