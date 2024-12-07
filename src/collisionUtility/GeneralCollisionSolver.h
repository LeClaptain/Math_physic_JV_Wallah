#pragma once

#include "GeneralCollisionDetector.h"

class GeneralCollisionSolver
{
public:
    void ResolveCollisions(std::vector<CollisionPair> collisions);

    void setElasticity(float newValue) { elasicity = newValue; }

private:
    void ResolveOneCollision(const CollisionPair& cp);

    float elasicity = 1.0f;
};
