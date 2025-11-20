
#include <random>
#include "patterns/Factory.h"
#include "core/Bestiole.h"
#include "behaviours/Anticipating.h"
#include "behaviours/Fearful.h"
#include "behaviours/Gregarious.h"
#include "behaviours/Kamikaze.h"
#include "behaviours/MultiPersonality.h"

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
    }

    return new Bestiole(std::move(behavior)); 
}
