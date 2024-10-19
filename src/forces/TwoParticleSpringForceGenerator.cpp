#include "TwoParticleSpringForceGenerator.h"

void TwoParticleSpringForceGenerator::updateForce(Particle* particle, float duration)
{
	vec3 distance = p1->getPosition() - p2->getPosition();
	float length = distance.magnitude();
	vec3 force = vec3(0);

	if (length != 0)
		force = distance.normalized() * (k * (l0 - length));

	if (particle == p1)
		particle->addForce(force);
	else
		particle->addForce(-force);
}
