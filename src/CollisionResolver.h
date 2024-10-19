#pragma once
#include "CollisionDetector.h"

class CollisionResolver
{
public:
    CollisionResolver();
    void resolveAllCollisions(std::vector<CollisionData>);
    void setElasticity(float newValue){ elasticity = newValue; }
private :

    Particle* particle1;
    Particle* particle2;
    vec3 normal;
    float elasticity = 1.0f;
    
    void resolveOneCollision(CollisionData data);

    float computeMagnitude() const;
};
