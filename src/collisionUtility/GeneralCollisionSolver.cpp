#include "GeneralCollisionSolver.h"

void GeneralCollisionSolver::ResolveCollisions(std::vector<CollisionPair> collisions)
{
    for (const CollisionPair& data : collisions)
    {
        ResolveOneCollision(data);
    }
}

void GeneralCollisionSolver::ResolveOneCollision(const CollisionPair& cp)
{
    if (!cp.atRest)
    {
        // first we displace the bodies
        // for that we need to calculate the displacement vector. It is the minimum displacement vector that will separate the two bodies.
        vec3 displacement(0);
        for (auto& point : cp.collisionPoints)
        {
            // find if we already displaced in the normal direction
            float current = displacement.dot(point.normal);
            float toAdd = point.penetration - current;
            displacement += point.normal * toAdd;
        }

        if (cp.body2->getunmoovable())
        {
            cp.body1->setPosition(cp.body1->getPosition() + displacement);
        }
        else if (cp.body1->getunmoovable())
        {
            cp.body2->setPosition(cp.body2->getPosition() - displacement);
        }
        else
        {
            float mass1 = cp.body1->getMass();
            float mass2 = cp.body2->getMass();

            float deltap1 = mass2 / (mass1 + mass2) * displacement.magnitude();
            float deltap2 = mass1 / (mass1 + mass2) * displacement.magnitude();

            cp.body1->setPosition(cp.body1->getPosition() + displacement.normalized() * deltap1);
            cp.body2->setPosition(cp.body2->getPosition() - displacement.normalized() * deltap2);
        }
    }


    vec3 vrel = cp.body1->getVelocity() - cp.body2->getVelocity();

    float totalPenetration = 0;
    for (auto& points : cp.collisionPoints)
    {
        totalPenetration += points.penetration;
    }
    
    // torque
    for (auto& points : cp.collisionPoints)
    {
        float penetration = points.penetration;
        float ratio = penetration / totalPenetration;
        
        float k = (vrel * ratio * (elasicity + 1)).dot(points.normal) / (cp.body1->getInverseMass() + cp.body2->
            getInverseMass());

        // linear velocity
        if (!cp.body1->getunmoovable())
        {
            cp.body1->setVelocity(cp.body1->getVelocity() - points.normal * k * cp.body1->getInverseMass());
        }
        if (!cp.body2->getunmoovable())
        {
            cp.body2->setVelocity(cp.body2->getVelocity() + points.normal * k * cp.body2->getInverseMass());
        }

        // angular velocity
        // point in local space
        vec3 r1 = points.point - cp.body1->getPosition();
        vec3 r2 = points.point - cp.body2->getPosition();

        vec3 torque1 = r1.cross(points.normal);
        vec3 torque2 = r2.cross(points.normal);

        if (!cp.body1->getunmoovable())
        {
            mat3 orientationMatrix = cp.body1->getOrientation().toMat3();
            mat3 JminusOnePrim = orientationMatrix * cp.body1->getJminusOne() * orientationMatrix.inverse();
            cp.body1->setAngularVelocity(cp.body1->getAngularVelocity() - torque1 * k * JminusOnePrim);
        }
        if (!cp.body2->getunmoovable())
        {
            mat3 orientationMatrix = cp.body2->getOrientation().toMat3();
            mat3 JminusOnePrim = orientationMatrix * cp.body2->getJminusOne() * orientationMatrix.inverse();
            cp.body2->setAngularVelocity(cp.body2->getAngularVelocity() + torque2 * k * JminusOnePrim);
        }
    }
}
