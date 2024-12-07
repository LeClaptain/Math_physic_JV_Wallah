#include "CollisionResolver.h"

#include <complex.h>

void CollisionResolver::resolveCollisions(std::vector<CollisionData> collisions)
{
    for (const CollisionData& data : collisions)
    {
        resolveOneCollision(data);
    }
}

void CollisionResolver::resolveOneCollision(CollisionData data)
{
    Particle* particle1 = data.particle1;
    Particle* particle2 = data.particle2;
    vec3 normal = data.normal;
    float mass1 = particle1->getMass();
    float mass2 = particle2 == nullptr ? 0.0f : particle2->getMass();
    float inverseMass1 = particle1->getInverseMass();
    float inverseMass2 = particle2 == nullptr ? 0.0f : particle2->getInverseMass();

    // If there is a collision and it is not at rest (small velocities)
    if (!data.atRest)
    {
        // Displacement
        if (particle2 == nullptr)
        {
            // ground
            particle1->setPosition(particle1->getPosition() + normal * data.penetration);
        }
        else
        {
            float deltap1 = mass2 / (mass1 + mass2) * data.penetration;
            float deltap2 = mass1 / (mass1 + mass2) * data.penetration;

            particle1->setPosition(particle1->getPosition() - normal * deltap1);
            particle2->setPosition(particle2->getPosition() + normal * deltap2);
        }
    }

    // Impulse resolution
    vec3 vrel = data.particle1->getVelocity() - (data.particle2 == nullptr ? vec3() : data.particle2->getVelocity());
    
    float k = (vrel * (elasticity + 1)).dot(normal) / (inverseMass1 + inverseMass2);

    particle1->setVelocity(particle1->getVelocity() - normal * k * inverseMass1);
    if (particle2 != nullptr)
    {
        particle2->setVelocity(particle2->getVelocity() + normal * k * inverseMass2);
    }
}
