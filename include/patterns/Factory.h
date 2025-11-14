#ifndef FACTORY_H
#define FACTORY_H

#include "IFactory.h"

class Factory : public IFactory {
 public:
  IBestiole* createBestiole() override;
};

#endif  // FACTORY_H