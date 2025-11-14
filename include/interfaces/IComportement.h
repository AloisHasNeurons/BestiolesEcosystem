#ifndef ICOMPORTEMENT_H
#define ICOMPORTEMENT_H

class IComportement {
 public:
  virtual ~IComportement() {}
  virtual double& diriger(double orientation) = 0;
};

#endif  // ICOMPORTEMENT_H