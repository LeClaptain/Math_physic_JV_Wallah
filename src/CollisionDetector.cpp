#include "CollisionDetector.h"

std::vector<CollisionData> CollisionDetector::detectAllCollisions()
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

            if (distance < sumRadius)
            {
                vec3 normal = (p2->getPosition() - p1->getPosition()).normalize();
                float penetration = sumRadius - distance;

                CollisionData data;
                data.particle1 = p1;
                data.particle2 = p2;
                data.normal = normal;
                data.penetration = penetration;

                collisions.push_back(data);
            }
        }
        float distanceToPlane = particles[i]->getPosition().y() - particles[i]->getRadius();
        if (distanceToPlane < 0 )
        {
            CollisionData data;
            data.particle1 = particles[i];
            data.particle2 = nullptr;
            data.normal = vec3(0, 1, 0);
            data.penetration = distanceToPlane;

            collisions.push_back(data);
        }
    }

    return collisions;
}

void CollisionDetector::addParticle(Particle* p)
{
    particles.push_back(p);
}
