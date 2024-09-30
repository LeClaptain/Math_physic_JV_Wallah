#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
    virtual ~ForceGenerator() = 0;

    virtual void updateForce(Particle *particle, float duration) = 0;
};
