
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

// We invite you to check the Readme.md file for instructions about how to run
// this project.
int main() {
    SimulationConfig config;
    SimulationMenu menu;

    menu.run(config); // This launches the menu to configure the simulation
                      // (go to Readme.md for more details)

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

    // Set Sensor Configurations
    SensorConfig eyeCfg;
    eyeCfg.deltaMin = config.eyesparams["minimum detection distance"];
    eyeCfg.deltaMax = config.eyesparams["maximum detection distance"];
    eyeCfg.alphaMin = config.eyesparams["minimum field-of-view angle"];
    eyeCfg.alphaMax = config.eyesparams["maximum field-of-view angle"];
    eyeCfg.gammaMin = config.eyesparams["lower bound of detection capability"];
    eyeCfg.gammaMax = config.eyesparams["upper bound of detection capability"];
    Aquarium::setEyeConfig(eyeCfg);

    SensorConfig earCfg;
    earCfg.deltaMin = config.earsparams["minimum detection distance"];
    earCfg.deltaMax = config.earsparams["maximum detection distance"];
    earCfg.alphaMin = 360.0; // Ears have full 360° field-of-view
    earCfg.alphaMax = 360.0; // Ears have full 360° field-of-view
    earCfg.gammaMin = config.earsparams["lower bound of detection capability"];
    earCfg.gammaMax = config.earsparams["upper bound of detection capability"];
    Aquarium::setEarConfig(earCfg);

    // Set Accessory Configurations
    AccessoryConfig accessoryCfg;
    accessoryCfg.nuMin = config.accessoriesparams["minimum speed factor for Fins"];
    accessoryCfg.nuMax = config.accessoriesparams["maximum speed factor for Fins"];
    accessoryCfg.tetaMin = config.accessoriesparams["minimum speed reduction factor for Shell"];
    accessoryCfg.tetaMax = config.accessoriesparams["maximum speed reduction factor for Shell"];
    accessoryCfg.omegaMin = config.accessoriesparams["minimum armor enhancement factor for Shell"];
    accessoryCfg.omegaMax = config.accessoriesparams["maximum armor enhancement factor for Shell"];
    accessoryCfg.camouflageMin = config.accessoriesparams["minimum camouflage value"];
    accessoryCfg.camouflageMax = config.accessoriesparams["maximum camouflage value"];
    Aquarium::setAccessoryConfig(accessoryCfg);

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