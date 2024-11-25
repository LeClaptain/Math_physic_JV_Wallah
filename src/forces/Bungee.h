#pragma once
#include "../ForceGenerator.h"
class Bungee : public ForceGenerator
{
protected:
    float bungeeConstant;
    float restLength;
    Particle* particle1;
    Particle* particle2;

public:
    Bungee(float bungeeConstant, float restLength, Particle* particle1, Particle* particle2) {
        this->bungeeConstant = bungeeConstant;
        this->restLength = restLength;
        this->particle1 = particle1;
        this->particle2 = particle2;
    }
    
    void updateForce(Particle* particle, float duration) override;

    void debugDraw() const override;
};

