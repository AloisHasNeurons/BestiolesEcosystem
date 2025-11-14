#ifndef MILIEU_H_
#define MILIEU_H_

#include <iostream>
#include <memory>
#include <vector>

#include "../UImg.h"
#include "interfaces/IBestiole.h"

class Milieu : public UImg {
 private:
  static const T white[];

  std::vector<IBestiole*> listeBestioles;

 public:
  Milieu(int _width, int _height);
  ~Milieu(void);

  void step(void);

  void addMember(IBestiole* b) {
    listeBestioles.push_back(b);
    b->initCoords(this->width(), this->height());
  }
  int nbVoisins(const IBestiole& b);
};

#endif