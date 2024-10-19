#pragma once
#include "Particle.h"
#include "vec3.h"

/**
 * Class used to find collisions between particles.
 * Will return pairs of particles that are colliding, and additional data needed for collision resolution.
 */

struct CollisionData
{
    Particle* particle1;
    Particle* particle2;
    vec3 normal;
    float penetration;
};

class CollisionDetector
{
public:

    /**
     * Finds collisions, displace particles so they are no longer colliding and then returns the collision data used for resolution.
     * @return A vector of CollisionData structs.
     */
    std::vector<CollisionData> detectAllCollisions();

    void addParticle(Particle* p);

private:
    std::vector<Particle*> particles;
};
