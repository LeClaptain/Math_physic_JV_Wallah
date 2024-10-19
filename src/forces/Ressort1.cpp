#include "forces/Ressort1.h"



void Ressort1::updateForce(Particle* particle, float duration)
{

	float length = (particle->getPosition() - ancre).magnitude();
	vec3 dir = (particle->getPosition() - ancre) / length;
	vec3 force = dir * this->springConstant * (restLength - length);
	// printf("force: %f, %f, %f\n", force.x(), force.y(), force.z());
	particle->addForce(force);
}