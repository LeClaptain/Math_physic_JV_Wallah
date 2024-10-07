#pragma once
#include "ForceGenerator.h"
#include "Particle.h"

class ForceRegistry
{
public:
    struct ParticleForceEntry
    {
        Particle* particle;
        ForceGenerator* generator;

        bool operator==(const ParticleForceEntry& other);
    };

    void add(Particle* p, ForceGenerator* generator);
    void remove(Particle* p, ForceGenerator* generator);
    void clear();
    void updateForces(float duration);

private:
    std::vector<ParticleForceEntry> entries;
};
