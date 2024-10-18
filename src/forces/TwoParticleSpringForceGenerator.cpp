#include "TwoParticleSpringForceGenerator.h"

void TwoParticleSpringForceGenerator::updateForce(Particle* particle, float duration)
{
	vec3 length = p1->getPosition() - p2->getPosition();
	vec3 force = length.normalize() * ( k * ( l0 - length.magnitude() ) );

	if (particle == p1)
		particle->addForce(-force);
	else
		particle->addForce(force);
}
