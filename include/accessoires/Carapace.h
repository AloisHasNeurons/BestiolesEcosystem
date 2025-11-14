#ifndef CARAPACE_H
#define CARAPACE_H

#include "../interfaces/IAccessoire.h"

class Carapace : public IAccessoire {
public:
    void changeParam() override;
    void draw() override;

private:
    double omega;
    double teta;
};

#endif // CARAPACE_H