#include <iostream>
#include <memory> // Required for std::unique_ptr

#include "core/Aquarium.h"
#include "core/Bestiole.h"
#include "core/Environment.h"

// Include behavior headers
#include "behaviors/Anticipating.h"
#include "behaviors/Fearful.h"
#include "behaviors/Gregarious.h"
#include "behaviors/Kamikaze.h"
#include "behaviors/MultiPersonality.h"

int main() {
  Aquarium ecosystem(640, 480, 30);

  // 1. Create 5 Gregarious Bestioles
  for (int i = 0; i < 5; ++i) {
    ecosystem.getEnvironment().addMember(
        new Bestiole(std::unique_ptr<Gregarious>(new Gregarious()))
    );
  }

  // 2. Create 5 Fearful Bestioles (with specific sensitivity parameters if desired)
  for (int i = 0; i < 5; ++i) {
    // Fearful constructor takes an optional 'max_neighbors' argument
    ecosystem.getEnvironment().addMember(
        new Bestiole(std::unique_ptr<Fearful>(new Fearful(3)))
    );
  }

  // 3. Create 5 Kamikaze Bestioles
  for (int i = 0; i < 5; ++i) {
    ecosystem.getEnvironment().addMember(
        new Bestiole(std::unique_ptr<Kamikaze>(new Kamikaze()))
    );
  }

  // 4. Create 5 Anticipating Bestioles
  for (int i = 0; i < 5; ++i) {
    ecosystem.getEnvironment().addMember(
        new Bestiole(std::unique_ptr<Anticipating>(new Anticipating()))
    );
  }

   // 5. Create 5 MultiPersonality Bestioles
  for (int i = 0; i < 5; ++i) {
    ecosystem.getEnvironment().addMember(
        new Bestiole(std::unique_ptr<MultiPersonality>(new MultiPersonality()))
    );
  }

  ecosystem.run();

  return 0;
}