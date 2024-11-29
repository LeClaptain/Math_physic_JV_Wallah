#pragma once
#include "BoundingVolume.h"
#include "CorpsRigide.h"
#include "Octree.h"

struct CollisionPair
{
    CorpsRigide* body1;
    CorpsRigide* body2;
    vec3 normal;
    bool atRest;
    float penetration;
};

class GeneralCollisionDetector
{
public:
    GeneralCollisionDetector(maths::vec3 octreePosition, maths::vec3 octreeExtent);
    void draw();
    std::vector<CollisionPair> DetectAllCollisions();
    void setBoundingVolumeVector(std::vector<BoundingVolume*>* volumes){this->volumes = volumes;}
    void setDebug(bool debug){this->debug = debug;}
private:
    bool debug = false;
    std::vector<BoundingVolume*>* volumes;
    std::vector<CollisionPair> collisionPairs;
    octree::Octree* octree;

    void detectCollisionForOneBoundingVolume(BoundingVolume *volume);
    std::vector<BoundingVolume*> octreeComputation(BoundingVolume* volume);
    bool doBoundingVolumesCollide(BoundingVolume* volume1, BoundingVolume* volume2);
    void SeperatingAxisCheck(BoundingVolume* volume1, BoundingVolume* volume2);
};

