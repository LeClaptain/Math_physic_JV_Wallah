#pragma once
#include "../ForceGenerator.h"

class GravityForceGenerator : ForceGenerator
{
public:
    void updateForce(Particle* particle, float duration) override;
};
