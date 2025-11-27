#ifndef EYES_H
#define EYES_H

#include "interfaces/ISensor.h"
#include "core/Environment.h"

class Eyes : public ISensor
{
private:
    double delta;     // seeing distance δ
    double alpha;     // field-of-view angle (radians)
    double gamma;     // detection capability γ

public:
    explicit Eyes(IBestiole* b);

    ~Eyes() override = default;

    void draw(UImg& img) override;

    bool canSee(const IBestiole& b) const override;
};

#endif  // EYES_H