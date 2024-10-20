#pragma once
#include "CollisionDetector.h"

class CollisionResolver
{
public:
    void resolveCollisions(std::vector<CollisionData>);
    void setElasticity(float newValue) { elasticity = newValue; }

private :
    float elasticity = 1.0f;

    void resolveOneCollision(CollisionData data);
};
