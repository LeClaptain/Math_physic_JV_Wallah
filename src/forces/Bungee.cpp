#include "Bungee.h"


void Bungee::updateForce(Particle* particle1, float duration)
{

	float length = (particle1->getPosition() - particle2->getPosition()).magnitude();
	vec3 dir = (particle1->getPosition() - particle2->getPosition()) / length;
	if (length <= restLength) return;
	vec3 force = dir * this->bungeeConstant * (restLength - length);
	// printf("force: %f, %f, %f\n", force.x(), force.y(), force.z());
	particle1->addForce(force);
}