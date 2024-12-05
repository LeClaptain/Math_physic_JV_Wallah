#pragma once
#include "BoundingVolume.h"
#include "CorpsRigides/CorpsRigide.h"
#include "Octree.h"

struct PointCollision
{
    maths::vec3 point;
    maths::vec3 normal;
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
    maths::vec3 point;
    maths::vec3 normal;
};

class GeneralCollisionDetector
{
public:
    GeneralCollisionDetector(maths::vec3 octreePosition, maths::vec3 octreeExtent);

    /* 
        TO DO: ajouter une méthode d'ajout de CorpsRigide.
        
        Sachant qu'on crée un nouvel octree dans le constructeur de GeneralCollisionDetector,
        ca veut dire qu'on doit ajouter les CorpsRigide dans l'octree ici. Ca implique aussi 
        qu'il faut créer les BoundingVolume ici aussi. D'ou le besoin d'une méthode dédiée.
    */

    void draw();
    std::vector<CollisionPair> DetectAllCollisions();
    void setDebug(bool debug){this->debug = debug;}
    void addBody(CorpsRigide* body);
    
private:
    bool debug = false;
    std::vector<BoundingVolume*> volumes;
    std::vector<CollisionPair> collisionPairs;
    octree::Octree* octree;

    void detectCollisionForOneBoundingVolume(BoundingVolume *volume);
    std::vector<BoundingVolume*> octreeComputation(BoundingVolume* volume);
    bool doBoundingVolumesCollide(BoundingVolume* volume1, BoundingVolume* volume2);

    void checkCollision(BoundingVolume* volume1, BoundingVolume* volume2);
};

