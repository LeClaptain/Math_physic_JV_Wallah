#pragma once
#include "../ForceGenerator.h"
#include "../maths/vec3.h"

class TwoParticleSpringForceGenerator : public ForceGenerator
{
private:
	Particle* p1; // first particle
	Particle* p2; // second particle
	float k; // stiffness constant of the spring
	float l0; // initial length of the spring

public:
	TwoParticleSpringForceGenerator(Particle* particle1, Particle* particle2, float k, float initialLength) { p1 = particle1; p2 = particle2; this->k = k; l0 = initialLength; }

	void updateForce(Particle* particle, float duration) override;

	void debugDraw() const override;

	Particle* getParticle1() const { return p1; }
	Particle* getParticle2() const { return p2; }
};

