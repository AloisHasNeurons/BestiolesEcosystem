#include <iostream>
#include "TestUtils.h"
#include "core/Aquarium.h"
#include "core/Environment.h"
#include "core/Bestiole.h"

void run_test_shell() {
    std::cout << "Running Test Scenario: Shell Accessory Effectiveness" << std::endl;
    std::cout << "Observation: Kamikaze Creatures equipped with Shell accessories should never die from collisions with creatures without shells and have lower speed." << std::endl;
    std::cout << "Close the simulation window to complete the test." << std::endl;

    // 1. Configure Eyes (Strong vision) and Shells
    SensorConfig cfg = Aquarium::getEyeConfig();
    cfg.alphaMin = 360.0;  
    cfg.alphaMax = 360.0; 
    cfg.deltaMin = 30.0;
    cfg.deltaMax = 40.0;
    cfg.gammaMin = 1.0;
    cfg.gammaMax = 1.0;
    Aquarium::setEyeConfig(cfg);

    AccessoryConfig accCfg = Aquarium::getAccessoryConfig();
    accCfg.tetaMin = 5; // high Speed reduction factor
    accCfg.tetaMax = 5;
    accCfg.omegaMin = 3.0; // high Armor enhancement factor
    accCfg.omegaMax = 3.0;
    Aquarium::setAccessoryConfig(accCfg);

    // 2. Initialize and Configure Elements of the simulation
    Aquarium ecosystem(800, 600, 30);
    Environment& env = ecosystem.getEnvironment();  
    env.resetPopulation();

    // 3. Configure distribution of sensors and accessories
    env.setEyesAccessoryDistribution({{"NoEyes", 0.0}, {"WithEyes", 1.0}});  // All have eyes to ensure the kamikaze behavior since we want to observe the results of collisions
    env.setEarsAccessoryDistribution({{"NoEars", 1.0}, {"WithEars", 0.0}});  // No need for ears
    env.setCamouflageAccessoryDistribution({{"NoCamouflage", 1.0}, {"WithCamouflage", 0.0}});  // No need for camouflage
    env.setFinsAccessoryDistribution({{"NoFins", 1.0}, {"WithFins", 0.0}});  // No fins so that the speed comparison is clear
    env.setShellAccessoryDistribution({{"NoShell", 0.5}, {"WithShell", 0.5}});  // half have shells

    // 4. Configure behavior distribution
    env.setBehaviorDistribution({
        {"Anticipating", 0.0},
        {"Fearfull", 0.0},
        {"Gregarious", 0.0},
        {"Kamikaze", 1.0},
        {"MultiPersonality", 0.0}
    });

    // 5. Run the simulation
    ecosystem.run();
}