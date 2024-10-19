#include "GravityForceGenerator.h"

void GravityForceGenerator::updateForce(Particle* particle, float duration)
{
    //particle->addForce(vec3(0, -9.81f, 0));
    particle->addForce(vec3(0, -20.0f, 0));

}
