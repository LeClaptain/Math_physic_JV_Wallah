#pragma once
#include "../ForceGenerator.h"
class Ressort :
    public ForceGenerator
{
protected:
    float springConstant;
    float restLength;
    vec3 ancre;

public:
    Ressort(float springConstant, float restLength, vec3 ancre) {
        this->springConstant = springConstant;
        this->restLength = restLength;
        this->ancre = ancre;
    }
    
	void updateForce(Particle* particle, float duration) override;

    void debugDraw() const override;
};

