#ifndef IFACTORY_H
#define IFACTORY_H

class IBestiole;  // Déclaration anticipée

class IFactory {
 public:
  virtual ~IFactory() {}
  virtual IBestiole* createBestiole() = 0;
};

#endif  // IFACTORY_H