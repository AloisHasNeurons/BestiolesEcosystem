
#include <iostream>
#include <memory>
#include <string>

#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"

// Include behavior headers
#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"

#include "menu/SimulationMenu.h"

int main() {
    SimulationConfig config;
    SimulationMenu menu;

    menu.run(config);

    // Apply Global Settings
    Bestiole::setMaxSpeed(config.maxSpeed);
    Bestiole::setMinSpeed(config.minSpeed);

    Aquarium ecosystem(config.width, config.height, config.delay);

    // Apply Environment Settings
    ecosystem.getEnvironment().setBehaviorDistribution(
        config.spawnProbabilities);
    // Convert simplified accessory map to specific maps
    ecosystem.getEnvironment().setEyesAccessoryDistribution(
        {{"NoEyes", 1.0 - config.accessories["Eyes"]},
         {"WithEyes", config.accessories["Eyes"]}});
    ecosystem.getEnvironment().setEarsAccessoryDistribution(
        {{"NoEars", 1.0 - config.accessories["Ears"]},
         {"WithEars", config.accessories["Ears"]}});
    ecosystem.getEnvironment().setFinsAccessoryDistribution(
        {{"NoFins", 1.0 - config.accessories["Fins"]},
         {"WithFins", config.accessories["Fins"]}});
    ecosystem.getEnvironment().setShellAccessoryDistribution(
        {{"NoShell", 1.0 - config.accessories["Shell"]},
         {"WithShell", config.accessories["Shell"]}});
    ecosystem.getEnvironment().setCamouflageAccessoryDistribution(
        {{"NoCamouflage", 1.0 - config.accessories["Camouflage"]},
         {"WithCamouflage", config.accessories["Camouflage"]}});

    SensorConfig eyeCfg;
    eyeCfg.deltaMin = 15.0; eyeCfg.deltaMax = 30.0;
    eyeCfg.alphaMin = 350.0; eyeCfg.alphaMax = 360.0;
    eyeCfg.gammaMin = 0.9; eyeCfg.gammaMax = 1.0;
    Aquarium::setEyeConfig(eyeCfg);

    SensorConfig earCfg;
    earCfg.deltaMin = 15.0; earCfg.deltaMax = 30.0;
    earCfg.gammaMin = 0.9; earCfg.gammaMax = 1.0;
    Aquarium::setEarConfig(earCfg);

    // Instantiate Initial Population
    for (const auto& pair : config.initialPopulation) {
        for (int i = 0; i < pair.second; ++i) {
            if (pair.first == "Gregarious") {
                ecosystem.getEnvironment().addMember(new Bestiole(
                    std::unique_ptr<Gregarious>(new Gregarious())));
            } else if (pair.first == "Fearful") {
                ecosystem.getEnvironment().addMember(new Bestiole(
                    std::unique_ptr<Fearful>(new Fearful(3))));
            } else if (pair.first == "Kamikaze") {
                ecosystem.getEnvironment().addMember(new Bestiole(
                    std::unique_ptr<Kamikaze>(new Kamikaze())));
            } else if (pair.first == "Anticipating") {
                ecosystem.getEnvironment().addMember(new Bestiole(
                    std::unique_ptr<Anticipating>(new Anticipating())));
            } else if (pair.first == "MultiPersonality") {
                ecosystem.getEnvironment().addMember(new Bestiole(
                    std::unique_ptr<MultiPersonality>(
                        new MultiPersonality())));
            }
        }
    }

    ecosystem.run();

    return 0;
}