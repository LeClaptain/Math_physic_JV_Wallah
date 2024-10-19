#pragma once
#include "../ForceGenerator.h"
class Ressort1 :
    public ForceGenerator
{
protected:
    float springConstant;
    float restLength;
    Particle* particle;
    vec3 ancre;

public:
    Ressort1(float springConstant, float restLength, Particle* particle, vec3 ancre) {
        this->springConstant = springConstant;
        this->restLength = restLength;
        this->particle = particle;
        this->ancre = ancre;
    };
	void updateForce(Particle* particle, float duration) override;
};

