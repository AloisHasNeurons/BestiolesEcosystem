#ifndef IFACTORY_H
#define IFACTORY_H

class IBestiole; // Forward declaration

class IFactory {
public:
  virtual ~IFactory() {}
  virtual IBestiole *createBestiole() = 0;
};

#endif // IFACTORY_H