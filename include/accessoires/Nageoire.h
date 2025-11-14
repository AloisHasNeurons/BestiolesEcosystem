#ifndef NAGEOIRE_H
#define NAGEOIRE_H

#include "../interfaces/IAccessoire.h"

class Nageoire : public IAccessoire {
public:
    void changeParam() override;
    void draw() override;

private:
    double nu;
};

#endif // NAGEOIRE_H