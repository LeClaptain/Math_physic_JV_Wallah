#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
    virtual ~ForceGenerator() = default;

    /**
     * Lowest priority is executed first
     * @return the priority of the force generator 
     */
    virtual int getPriority() const { return 0; }

    virtual void updateForce(Particle *particle, float duration) = 0;

    virtual void debugDraw() const {};
};
