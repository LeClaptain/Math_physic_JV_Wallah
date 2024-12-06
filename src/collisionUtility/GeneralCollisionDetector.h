#pragma once
#include "BoundingVolume.h"
#include "CorpsRigides/CorpsRigide.h"
#include "Octree.h"

struct PointCollision
{
    vec3 point;
    vec3 normal;
    float penetration;
};

struct CollisionPair
{
    CorpsRigide* body1;
    CorpsRigide* body2;
    vec3 normal;
    std::vector<PointCollision> PointCollisions;
    bool atRest;
};


struct Face
{
    vec3 point;
    vec3 normal;
};

class GeneralCollisionDetector
{
public:
    GeneralCollisionDetector(vec3 octreePosition, vec3 octreeExtent);

    /* 
        TO DO: ajouter une méthode d'ajout de CorpsRigide.
        
        Sachant qu'on crée un nouvel octree dans le constructeur de GeneralCollisionDetector,
        ca veut dire qu'on doit ajouter les CorpsRigide dans l'octree ici. Ca implique aussi 
        qu'il faut créer les BoundingVolume ici aussi. D'ou le besoin d'une méthode dédiée.
    */

    std::vector<CollisionPair> FindAllCollisions();
    void setDebug(bool debug) { this->debug = debug; }
    void addBody(CorpsRigide* body);

private:
    bool debug = false;
    vec3 position, extent;
    std::vector<CorpsRigide*> bodies;

    std::vector<CollisionPair> FindCollisionsForOneBoundingVolume(const octree::Octree& o, BoundingVolume* volume);
    std::vector<BoundingVolume*> FindPotientialCollidingColliders(const octree::Octree& o, BoundingVolume* volume);
    bool BoundingVolumesMightCollide(BoundingVolume* volume1, BoundingVolume* volume2);

    bool FindCollisionPointsIfAny(BoundingVolume* volume1, BoundingVolume* volume2, CollisionPair* cp);
};
