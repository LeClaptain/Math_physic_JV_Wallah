#include "GeneralCollisionDetector.h"

GeneralCollisionDetector::GeneralCollisionDetector(maths::vec3 octreePosition, maths::vec3 octreeExtent)
{
    octree = new octree::Octree(octree::OTBox(octreePosition, octreeExtent));
    /*for (int i = 0; i < 100; i++)
    {
        auto position = maths::vec3((std::rand() % 1000) - 500, (std::rand() % 1000) - 500, (std::rand() % 1000) - 500);
        
        octree->add(new BoundingVolume(5.0f, position));
    }*/
}

void GeneralCollisionDetector::draw()
{
    if(debug)
    {
        octree->draw();
    }
}

std::vector<CollisionPair> GeneralCollisionDetector::DetectAllCollisions()
{
    collisionPairs = std::vector<CollisionPair>();
    if (!volumes)
    {
        std::cout << "volumes is nullptr, therefore everything that follows is baaaad" << std::endl;
    }
    for (auto volume = volumes->begin(); volume != volumes->end(); volume++)
    {
        detectCollisionForOneBoundingVolume(*volume);
    }
    return collisionPairs;
}

void GeneralCollisionDetector::detectCollisionForOneBoundingVolume(BoundingVolume* volume)
{
    std::vector<BoundingVolume*> potentialColliders = octreeComputation(volume);
    if (potentialColliders.size() <= 1){return;}

    for (auto potentialCollider = potentialColliders.begin(); potentialCollider != potentialColliders.end(); volume++)
    {
        if (*potentialCollider == volume){continue;}
        if (doBoundingVolumesCollide(volume, *potentialCollider))
        {
            SeperatingAxisCheck(volume, *potentialCollider);
        }
    }
}


std::vector<BoundingVolume*> GeneralCollisionDetector::octreeComputation(BoundingVolume* volume)
{
    float radius = volume->getRadius();
    vec3 position = volume->getCenter();
    octree::OTBox queryBox(position, vec3(radius));
    std::vector<BoundingVolume*> potentialCollisions = octree->query(queryBox);
    return potentialCollisions;
}

bool GeneralCollisionDetector::doBoundingVolumesCollide(BoundingVolume* volume1, BoundingVolume* volume2)
{
    if (volume1->getCenter().distance(volume2->getCenter()) < volume1->getRadius() + volume2->getRadius())
    {
        return true;
    }
    return false;
}

void GeneralCollisionDetector::SeperatingAxisCheck(BoundingVolume* volume1, BoundingVolume* volume2)
{
    of3dPrimitive* mesh1 = volume1->getRigidBody();
    of3dPrimitive* mesh2 = volume2->getRigidBody();

}
