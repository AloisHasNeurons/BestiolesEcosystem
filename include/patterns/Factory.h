#ifndef FACTORY_H
#define FACTORY_H

#include "IFactory.h"
#include "Environment.h"

class Factory : public IFactory {
 private:
  const Environment& env; // Reference to the Environment that may influence Bestiole creation
  
 public:
  Factory(const Environment& env); // Constructor with Environment reference
  IBestiole* createBestiole() override; // Method to create a new Bestiole

 
};

#endif  // FACTORY_H