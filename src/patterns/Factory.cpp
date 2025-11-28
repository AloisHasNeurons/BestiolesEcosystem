
#include <random>
#include <memory>
#include "patterns/Factory.h"
#include "core/Bestiole.h"
#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"
#include "sensors/Eyes.h"
#include "sensors/Ears.h"
#include "accessories/Camouflage.h"
#include "accessories/Fin.h"
#include "accessories/Shell.h"

Factory::Factory(const Environment& env) // Constructor with Environment reference
    : env(env)
{}

IBestiole* Factory::createBestiole() 
{
    // Get behavior probabilities from the environment
    auto probs = env.getBehaviorDistribution(); // Assume this method exists

    static std::random_device rd;
    static std::mt19937 gen(rd()); // Random number generator

    // discrete distribution based on probabilities
    std::discrete_distribution<int> dist(probs.begin(), probs.end());

    int choice = dist(gen);

    std::unique_ptr<IBehavior> behavior;

    switch(choice) {
        case 0: behavior = std::make_unique<Anticipating>(); break;
        case 1: behavior = std::make_unique<Fearful>(); break;
        case 2: behavior = std::make_unique<Gregarious>(); break;
        case 3: behavior = std::make_unique<Kamikaze>(); break;
        case 4: behavior = std::make_unique<MultiPersonality>(); break;
        default: behavior = std::make_unique<Anticipating>(); break;
    }

    // Create and return a new Bestiole with the selected behavior
    Bestiole* plainBestiole = new Bestiole(std::move(behavior)); 
    
    // Randomly add eyes based on environment settings
    auto eyesProbs = env.getEyesAccessoryDistribution(); // Assume this method exists
    std::discrete_distribution<int> accDist(eyesProbs.begin(), eyesProbs.end());
    int accChoice = accDist(gen);

    if (accChoice == 1) { // If the choice is to add eyes
        // wrap the existing Bestiole with an Eyes decorator without redeclaring the variable
        plainBestiole = new Eyes(plainBestiole);
    }

    // Randomly add other accessories similarly...
    auto earsProbs = env.getEarsAccessoryDistribution(); // Assume this method exists
    std::discrete_distribution<int> earsDist(earsProbs.begin(), earsProbs.end());
    int earsChoice = earsDist(gen);

    if (earsChoice == 1) { // If the choice is to add ears
        // wrap the existing Bestiole with an Ears decorator without redeclaring the variable
        plainBestiole = new Ears(plainBestiole);
    }

    auto camouflageProbs = env.getCamouflageAccessoryDistribution(); // Assume this method exists
    std::discrete_distribution<int> camoDist(camouflageProbs.begin(), camouflageProbs.end());
    int camoChoice = camoDist(gen);

    if (camoChoice == 1) { // If the choice is to add camouflage
        // wrap the existing Bestiole with a Camouflage decorator without redeclaring the variable
        plainBestiole = new Camouflage(plainBestiole);
    }

    auto finProbs = env.getFinsAccessoryDistribution(); // Assume this method exists
    std::discrete_distribution<int> finDist(finProbs.begin(), finProbs.end());
    int finChoice = finDist(gen);

    if (finChoice == 1) { // If the choice is to add fins
        // wrap the existing Bestiole with a Fins decorator without redeclaring the variable
        plainBestiole = new Fin(plainBestiole);
    }

    auto shellProbs = env.getShellAccessoryDistribution(); // Assume this method exists
    std::discrete_distribution<int> shellDist(shellProbs.begin(), shellProbs.end());
    int shellChoice = shellDist(gen);

    if (shellChoice == 1) { // If the choice is to add shell
        // wrap the existing Bestiole with a Shell decorator without redeclaring the variable
        plainBestiole = new Shell(plainBestiole);
    }

    return plainBestiole;
}


