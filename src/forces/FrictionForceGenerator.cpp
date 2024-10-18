#include "FrictionForceGenerator.h"

void FrictionForceGenerator::updateForce(Particle* particle, float duration)
{
	vec3 velocity = particle->getVelocity();
	float speed = velocity.magnitude();

	vec3 force = -velocity.normalize() * (k1 * speed + k2 * speed * speed);

	particle->addForce(force);
}
