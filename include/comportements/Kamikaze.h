#ifndef KAMIKAZE_H
#define KAMIKAZE_H

#include "../interfaces/IComportement.h"

// Déclaration anticipée
class Bestiole;

class Kamikaze : public IComportement {
 public:
  double& diriger(double orientation) override;
  Bestiole plusProcheVoisin();  // Attention au retour par copie
};

#endif  // KAMIKAZE_H