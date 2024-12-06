#include "GeneralCollisionDetector.h"

#include "CollisionDetector.h"
#include "of3dGraphics.h"
#include "ofGraphics.h"
#include "CorpsRigides/Box.h"

GeneralCollisionDetector::GeneralCollisionDetector(vec3 octreePosition, vec3 octreeExtent) : position(octreePosition),
    extent(octreeExtent)
{
}

std::vector<CollisionPair> GeneralCollisionDetector::FindAllCollisions()
{
    auto pairs = std::vector<CollisionPair>();

    // auto otbox = octree::OTBox(position, extent);
    // octree::Octree o = octree::Octree(otbox);
    std::vector<BoundingVolume> volumes;

    for (auto& body : bodies)
    {
        volumes.push_back(BoundingVolume(body));
        // o.add(&volumes.back());
        // volumes.back().draw();
    }

    // if (debug)
    // {
    //     o.draw();
    // }

    // for (auto& volume : volumes)
    // {
    //     auto collisions = FindCollisionsForOneBoundingVolume(o, &volume);
    //     pairs.insert(pairs.end(), collisions.begin(), collisions.end());
    // }

    for (int i = 0; i < volumes.size(); i++)
    {
        for (int j = i + 1; j < volumes.size(); j++)
        {
            if (volumes[i].getRigidBody() == volumes[j].getRigidBody()) { continue; }
            if (BoundingVolumesMightCollide(&volumes[i], &volumes[j]))
            {
                CollisionPair cp;
                if (FindCollisionPointsIfAny(&volumes[i], &volumes[j], &cp))
                {
                    pairs.push_back(cp);
                }
            }
        }
    }

    return pairs;
}

void GeneralCollisionDetector::addBody(CorpsRigide* body)
{
    bodies.push_back(body);
}

std::vector<CollisionPair> GeneralCollisionDetector::FindCollisionsForOneBoundingVolume(
    const octree::Octree& o, BoundingVolume* volume)
{
    std::vector<BoundingVolume*> potentialColliders = FindPotientialCollidingColliders(o, volume);
    std::vector<CollisionPair> result;
    if (potentialColliders.size() <= 1) { return {}; }

    for (auto& potentialCollider : potentialColliders)
    {
        if (potentialCollider->getRigidBody() == volume->getRigidBody()) { continue; }
        if (BoundingVolumesMightCollide(volume, potentialCollider))
        {
            CollisionPair cp;
            if (FindCollisionPointsIfAny(volume, potentialCollider, &cp))
            {
                result.push_back(cp);
            }
        }
    }

    return result;
}


std::vector<BoundingVolume*> GeneralCollisionDetector::FindPotientialCollidingColliders(
    const octree::Octree& o, BoundingVolume* volume)
{
    float radius = volume->getRadius();
    vec3 position = volume->getCenter();
    octree::OTBox queryBox = octree::OTBox(vec3(radius), position); // 1.5 was here
    std::vector<BoundingVolume*> potentialCollisions = o.query(queryBox);
    return potentialCollisions;
}

bool GeneralCollisionDetector::BoundingVolumesMightCollide(BoundingVolume* volume1, BoundingVolume* volume2)
{
    if (volume1->getCenter().distance(volume2->getCenter()) < volume1->getRadius() + volume2->getRadius())
    {
        return true;
    }
    return false;
}

bool GeneralCollisionDetector::FindCollisionPointsIfAny(BoundingVolume* volume1, BoundingVolume* volume2,
                                                        CollisionPair* cp)
{
    auto v1Center = volume1->getRigidBody()->getPosition();
    auto v1HalfExtent = volume1->getRigidBody()->getExtent() / 2.f;
    auto v1Orientation = volume1->getRigidBody()->getOrientation().toMat3();
    auto v2Center = volume2->getRigidBody()->getPosition();
    auto v2HalfExtent = volume2->getRigidBody()->getExtent() / 2.f;
    auto v2Orientation = volume2->getRigidBody()->getOrientation().toMat3();

    vec3 rightTopFront_vertex = v2Center + v2Orientation * v2HalfExtent;
    vec3 leftBottomBack_vertex = v2Center + v2Orientation * -v2HalfExtent;

    std::vector<Face> faces;
    faces.push_back({rightTopFront_vertex, v2Orientation * vec3(1, 0, 0)});
    faces.push_back({rightTopFront_vertex, v2Orientation * vec3(0, 1, 0)});
    faces.push_back({rightTopFront_vertex, v2Orientation * vec3(0, 0, 1)});
    faces.push_back({leftBottomBack_vertex, v2Orientation * vec3(-1, 0, 0)});
    faces.push_back({leftBottomBack_vertex, v2Orientation * vec3(0, -1, 0)});
    faces.push_back({leftBottomBack_vertex, v2Orientation * vec3(0, 0, -1)});

    // draw each normal
    for (auto& face : faces)
    {
        ofDrawSphere(face.point, 5);
        ofDrawLine(face.point, face.point + face.normal * 100);
    }

    std::vector<vec3> vertices;
    vertices.push_back(v1Center + v1Orientation * vec3(v1HalfExtent.x(), v1HalfExtent.y(), v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(v1HalfExtent.x(), v1HalfExtent.y(), -v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(v1HalfExtent.x(), -v1HalfExtent.y(), v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(v1HalfExtent.x(), -v1HalfExtent.y(), -v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(-v1HalfExtent.x(), v1HalfExtent.y(), v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(-v1HalfExtent.x(), v1HalfExtent.y(), -v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(-v1HalfExtent.x(), -v1HalfExtent.y(), v1HalfExtent.z()));
    vertices.push_back(v1Center + v1Orientation * vec3(-v1HalfExtent.x(), -v1HalfExtent.y(), -v1HalfExtent.z()));

    std::vector<PointCollision> collisions;
    for (auto& vertex : vertices)
    {
        std::vector<PointCollision> potentialCollisions;
        int insideOther = 6;
        for (auto& face : faces)
        {
            float t = face.normal.dot(vertex - face.point);
            if (t < 0)
            {
                insideOther -= 1;
                potentialCollisions.push_back({vertex - face.normal * t, face.normal, -t});
            }
        }
        if (insideOther == 0)
        {
            int min = 0;
            for (int i = 1; i < potentialCollisions.size(); i++)
            {
                if (potentialCollisions[i].penetration < potentialCollisions[min].penetration)
                {
                    min = i;
                }
            }
            collisions.push_back(potentialCollisions[min]);
        }
    }

    CollisionPair colPair;
    colPair.body1 = volume1->getRigidBody();
    colPair.body2 = volume2->getRigidBody();
    colPair.collisionPoints = collisions; // erreur de conversion
    colPair.atRest = volume1->getRigidBody()->getVelocity() == vec3(0) && volume2->getRigidBody()->getVelocity() ==
        vec3(0);

    if (!colPair.collisionPoints.empty())
    {
        *cp = colPair;
        return true;
    }

    return false;
}
