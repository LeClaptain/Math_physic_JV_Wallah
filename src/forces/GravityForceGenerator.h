#pragma once
#include "../ForceGenerator.h"

class GravityForceGenerator : public ForceGenerator
{
public:
    void updateForce(Particle* particle, float duration) override;
};
