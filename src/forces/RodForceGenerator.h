#pragma once
#include "ForceGenerator.h"
class RodForceGenerator : public ForceGenerator
{
private:
	Particle* p1;
	Particle* p2;

public:
	RodForceGenerator(Particle* p1, Particle* p2) { this->p1 = p1; this->p2 = p2; }

	void updateForce(Particle* particle, float duration) override;
};

