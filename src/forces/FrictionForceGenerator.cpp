#include "FrictionForceGenerator.h"
#include <iostream>

void FrictionForceGenerator::updateForce(Particle* particle, float duration)
{
	vec3 velocity = particle->getVelocity();
	float speed = velocity.magnitude();

	vec3 force = vec3(0);
	if (speed != 0)
		force = -velocity.normalized() * (k1 * speed + k2 * speed * speed);

	particle->addForce(force);
}
