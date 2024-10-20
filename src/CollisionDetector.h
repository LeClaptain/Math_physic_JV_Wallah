#pragma once
#include "Particle.h"
#include "vec3.h"

struct CollisionData
{
    Particle* particle1;
    Particle* particle2;
    vec3 normal;
    bool atRest;
    float penetration;
};

enum RelationType
{
    CABLE,
    ROD
};

struct Relation
{
    Particle* p1;
    Particle* p2;
    float length;
    RelationType type;
};

/**
 * Class used to find collisions between particles.
 * Will return pairs of particles that are colliding, and additional data needed for collision resolution.
 */
class CollisionDetector
{
public:
    /**
     * Finds collisions, displace particles so they are no longer colliding and then returns the collision data used for resolution.
     * @return A vector of CollisionData structs.
     */
    std::vector<CollisionData> solve(double dt);

    void addParticle(Particle* p);

    void setGroundHeight(float height) { groundHeight = height; }

    void setGravity(float g) { gravity = g; }

    void addRelation(RelationType type, Particle* p1, Particle* p2, float length);

    void debugDrawRelations();

private:
    float groundHeight = 0;
    float gravity = 9.81f;
    std::vector<Particle*> particles;
    std::vector<Relation> relations;
};
