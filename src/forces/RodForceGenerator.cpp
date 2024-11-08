#include "RodForceGenerator.h"

void RodForceGenerator::updateForce(Particle* particle, float duration)
{
	vec3 forces1 = p1->getForces();
	vec3 forces2 = p2->getForces();

	p1->addForce(forces2);
	p2->addForce(forces1);
}
