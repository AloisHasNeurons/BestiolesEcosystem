#ifndef EARS_H
#define EARS_H

#include "../interfaces/ISensor.h"

class Ears : public ISensor
{
private:
    double deltaMin;  // minimum viewing distance
    double deltaMax;  // maximum viewing distance
    double gamma;     // detection capability γ

public:

    explicit Ears(IBestiole* b);

    ~Ears() override = default;

    void draw(UImg& img) override;

    bool canSee(const IBestiole& b) const override;
};

#endif  // EARS_H