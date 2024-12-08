#pragma once

#include "../CorpsRigides/CorpsRigide.h"

class Integrateur
{
public:
    void integrer(double dt, CorpsRigide* corpsRigide);

    void setDamping(float damping) { this->damping = damping; }

private:
    float damping = 0.0f;
};
