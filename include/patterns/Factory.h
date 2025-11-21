#ifndef FACTORY_H
#define FACTORY_H

#include "IFactory.h"

class Environment;

class Factory : public IFactory {
 private:
  const Environment* env;

 public:
  Factory();
  void setEnvironment(const Environment* env);
  IBestiole* createBestiole() override;
};

#endif