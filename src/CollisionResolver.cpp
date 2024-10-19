#include "CollisionResolver.h"

#include <complex.h>

CollisionResolver::CollisionResolver()
{
}

void CollisionResolver::resolveAllCollisions(std::vector<CollisionData> collisions)
{
    for (const CollisionData& data : collisions)
    {
        resolveOneCollision(data);
    }
        
}

void CollisionResolver::resolveOneCollision(CollisionData data)
{
    particle1 = data.particle1;
    particle2 = data.particle2;
    normal = data.normal;
    float magnitude = computeMagnitude();
    particle1->setVelocity(normal * (-magnitude));
    particle2->setVelocity(normal * magnitude);
}

float CollisionResolver::computeMagnitude() const
{
    vec3 relativeSpeed = particle1->getVelocity() - particle2->getVelocity();
    float mass1 = particle1->getInverseMass();
    float mass2 = particle2->getInverseMass();

    float magnitude = relativeSpeed.dot(normal)*(elasticity + 1) / (mass1 + mass2);
    return magnitude;
}
