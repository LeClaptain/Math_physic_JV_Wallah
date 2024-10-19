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
    if(particle2 != nullptr)
    {
        particle2->setVelocity(normal * magnitude);
    }
    else
    {
        vec3 positionP1 = particle1->getPosition();
        vec3 newPosition = vec3(particle1->getPosition().x(), positionP1.y() - data.penetration, particle1->getPosition().z());
        particle1->setPosition(newPosition);
        std::cout << particle1 << " " << particle2 << std::endl;
    }
}

float CollisionResolver::computeMagnitude() const
{
    vec3 relativeSpeed;
    float mass1 = particle1->getInverseMass();
    float mass2;
    float magnitude;
    if(particle2 == nullptr)
    {
        mass2 = 0.0f;
        relativeSpeed = particle1->getVelocity()*0.95;
        magnitude = relativeSpeed.dot(normal)*(0.1 + 1) / (mass1 + mass2);

    }
    else
    {
        mass2 = particle2->getInverseMass();
        relativeSpeed = particle1->getVelocity() - particle2->getVelocity();
        magnitude = relativeSpeed.dot(normal)*(elasticity + 1) / (mass1 + mass2);
    }
    
    return magnitude;
}
