#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../UImg.h"
#include "interfaces/IBestiole.h"

class Environment : public UImg {
 private:
  static const T white[];

  std::vector<IBestiole*> bestiolesList;

 public:
  Environment(int _width, int _height);
  ~Environment(void);

  void step(void);

  void addMember(IBestiole* b) {
    bestiolesList.push_back(b);
    b->initCoords(this->width(), this->height());
  }

  int neighborCount(const IBestiole& b);
};

#endif