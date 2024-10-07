#include "ForceRegistry.h"

bool ForceRegistry::ParticleForceEntry::operator==(const ParticleForceEntry& other)
{
    return particle == other.particle && generator == other.generator;
}

void ForceRegistry::add(Particle* p, ForceGenerator* generator)
{
    entries.push_back({p, generator});
}

void ForceRegistry::remove(Particle* p, ForceGenerator* generator)
{
    entries.erase(std::find(entries.begin(), entries.end(), ParticleForceEntry{p, generator}));
}

void ForceRegistry::clear()
{
    entries = {};
}

void ForceRegistry::updateForces(float duration)
{
    for (auto &entry : entries)
    {
        entry.generator->updateForce(entry.particle, duration);
    }
}



