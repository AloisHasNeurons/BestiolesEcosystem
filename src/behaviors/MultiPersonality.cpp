#include "behaviors/MultiPersonality.h"
#include "interfaces/IBestiole.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/Anticipating.h"
#include <cstdlib>
#include <chrono>

double MultiPersonality::steer(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
    return currentBehavior->steer(b, bestiolesList);
}

double MultiPersonality::speed(IBestiole& b, std::vector<IBestiole*> bestiolesList) {
    return currentBehavior->speed(b, bestiolesList);
}

void MultiPersonality::changeBehavior() {
    auto now = std::chrono::steady_clock::now();
    if (now - lastChange > std::chrono::seconds(4)) { // time based behavioral change
        int behaviorType = rand() % 4;
        delete currentBehavior;  // Free the memory of the old behavior
        switch (behaviorType) {
            case 0:
                currentBehavior = new Fearful(rand() % 5 + 4); // Random max_neighbors between 4 and 8
                break;
            case 1:
                currentBehavior = new Gregarious();
                break;
            case 2:
                currentBehavior = new Kamikaze();
                break;
            case 3:
                currentBehavior = new Anticipating();
                break;
        }
        lastChange = now;
    }   
}

MultiPersonality::MultiPersonality() {
    // Initialize with a random behavior
    int behaviorType = rand() % 4;
    switch (behaviorType) {
        case 0:
            currentBehavior = new Fearful(rand() % 5 + 4); // Random max_neighbors between 4 and 8
            break;
        case 1:
            currentBehavior = new Gregarious();
            break;
        case 2:
            currentBehavior = new Kamikaze();
            break;
        case 3:
            currentBehavior = new Anticipating();
            break;
    }
    lastChange = std::chrono::steady_clock::now();
    // Set initial color
    color = currentBehavior->getColor();
}

MultiPersonality::~MultiPersonality() {
    delete currentBehavior;
}