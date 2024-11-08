#include "CollisionSolver.h"

std::vector<CollisionSolver::CollisionData> CollisionSolver::solve()
{
    std::vector<CollisionData> collisions;

    for (int i = 0; i < particles.size(); i++)
    {
        for (int j = i + 1; j < particles.size(); j++)
        {
            Particle* p1 = particles[i];
            Particle* p2 = particles[j];

            float distance = (p1->getPosition() - p2->getPosition()).magnitude();
            float sumRadius = p1->getRadius() + p2->getRadius();
            float sumMass = p1->getMass() + p2->getMass();
            float oneOverSumMass = 1.0f / sumMass;

            if (distance < sumRadius)
            {
                // Collision detected
                vec3 normal = (p2->getPosition() - p1->getPosition()).normalize();
                float penetration = sumRadius - distance;

                // Displace particles
                p1->position -= normal * penetration * p2->getMass() * oneOverSumMass;
                p2->position += normal * penetration * p1->getMass() * oneOverSumMass;

                CollisionData data;
                data.particle1 = p1;
                data.particle2 = p2;
                data.normal = normal;
                data.penetration = penetration;

                collisions.push_back(data);
            }
        }
    }

    return collisions;
}

void CollisionSolver::addParticle(Particle* p)
{
    particles.push_back(p);
}
