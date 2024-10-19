#include "forces/Ressort1.h"



void Ressort1::updateForce(Particle* particle, float duration)
{

	float length = (particle->getPosition() - ancre).magnitude();
	vec3 dir = vec3(0, 0, 0);
	if (length != 0.0f)
	{
		dir = (particle->getPosition() - ancre).normalized(); 
	}
	vec3 force = dir * this->springConstant * (restLength - length);
	std::cout<<((std::string)particle->getPosition()) << std::endl;
	particle->addForce(force);
}