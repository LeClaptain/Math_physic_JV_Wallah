#include "ForceRegistry.h"

bool ForceRegistry::ParticleForceEntry::operator==(const ParticleForceEntry& other)
{
    return particle == other.particle && generator == other.generator;
}

void ForceRegistry::add(Particle* p, ForceGenerator* generator)
{
    entries.push_back({p, generator});

    std::sort(entries.begin(), entries.end(), [](const ParticleForceEntry& a, const ParticleForceEntry& b) {
        return a.generator->getPriority() < b.generator->getPriority();
    });
}

void ForceRegistry::add(std::vector<Particle*> p, ForceGenerator* generator)
{
    for (Particle* particle : p)
    {
        add(particle, generator);
    }
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



