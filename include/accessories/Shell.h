#ifndef SHELL_H
#define SHELL_H

#include "../interfaces/IAccessory.h"

class Shell : public IAccessory {
public:
    void updateParameters() override;
    void draw() override;

private:
    double omega;
    double teta;
};

#endif // SHELL_H