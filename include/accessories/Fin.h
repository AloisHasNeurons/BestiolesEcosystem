#ifndef FIN_H
#define FIN_H

#include "../interfaces/IAccessory.h"

class Fin : public IAccessory {
public:
    Fin(IBestiole* b);
    ~Fin() override = default;
    
    void action(Environment& env) override;
    void draw(UImg& img) override;

private:
    double nu;
};

#endif