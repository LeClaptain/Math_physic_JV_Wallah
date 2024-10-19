#pragma once
#include "ForceGenerator.h"
class FrictionForceGenerator : public ForceGenerator
{
private:
	float k1; // first friction constant (low speed)
	float k2; // second friction constant (high speed)

public:

	FrictionForceGenerator(float k1, float k2) { this->k1 = k1; this->k2 = k2; }

	void updateForce(Particle* particle, float duration) override;

};

