#ifndef SHELL_H
#define SHELL_H

#include "../interfaces/IAccessory.h"

class Shell : public IAccessory {
public:
    Shell(IBestiole* b, double _omega, double _teta);
    ~Shell() override = default;
    void draw(UImg& img) override;

    void action(Environment& env) override;
    void draw(UImg& img) override;
    
private:
    double omega;
    double teta;
};

#endif