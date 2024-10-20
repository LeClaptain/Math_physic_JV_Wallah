#include "CollisionDetector.h"

#include "ofGraphics.h"

std::vector<CollisionData> CollisionDetector::solve(double dt)
{
    std::vector<CollisionData> collisions;

    // first resolve relations
    for (Relation& r : relations)
    {
        vec3 delta = r.p2->getPosition() - r.p1->getPosition();
        float distance = delta.magnitude();
        float difference = distance - r.length;

        if (r.type == CABLE)
        {
            if (difference > 0)
            {
                vec3 normal = delta.normalize();
                collisions.push_back({r.p1, r.p2, normal, false, -difference});
            }
        }
        else if (r.type == ROD)
        {
            if (difference != 0)
            {
                vec3 normal = delta.normalize();
                collisions.push_back({r.p1, r.p2, normal, false, -difference});
            }
        }
    }

    for (int i = 0; i < particles.size(); i++)
    {
        Particle* p1 = particles[i];
        for (int j = i + 1; j < particles.size(); j++)
        {
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
                data.atRest = gravity * dt > p1->getVelocity().magnitude() || gravity * dt > p2->getVelocity().
                    magnitude();
                data.penetration = penetration;

                collisions.push_back(data);
            }
        }

        // ground
        float distanceToPlane = p1->getPosition().y() - p1->getRadius();
        if (distanceToPlane < 0)
        {
            CollisionData data;
            data.particle1 = p1;
            data.particle2 = nullptr;
            data.normal = vec3(0, -1, 0);
            data.atRest = gravity * dt > p1->getVelocity().magnitude();
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

void CollisionDetector::addRelation(RelationType type, Particle* p1, Particle* p2, float length)
{
    relations.push_back({p1, p2, length, type});
}

void CollisionDetector::debugDrawRelations()
{
    for (Relation& r : relations)
    {
        if (r.type == CABLE)
        {
            vec3 delta = r.p2->getPosition() - r.p1->getPosition();
            float distance = delta.magnitude();
            float difference = distance - r.length;

            if (difference > 0)
                ofSetColor(0, 0, 255);
            else
                ofSetColor(0, 255, 0);
        }
        else if (r.type == ROD)
            ofSetColor(255, 0, 0);
        
        ofDrawLine(r.p1->getPosition(), r.p2->getPosition());
    }
}
