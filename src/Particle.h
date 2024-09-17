#pragma once
#include "ofColor.h"
#include "ofUtils.h"
#include "maths/mat3.h"

#include <deque>

using namespace maths;

class Particle
{
private :
    vec3 position = vec3(0);
    vec3 velocity = vec3(0);
    vec3 defaultVelocity = vec3(0);
    vec3 acceleration = vec3(0);
    float mass = 0.0;
    float radius = 0.0;
    ofColor color = ofColor::white;
    bool hasTrail;
    float trailSegmentLength;
    int trailSegmentCount;
    std::string name;

    std::deque<vec3> segmentPoints;

public:
    Particle() = default;

    Particle(vec3 position, vec3 velocity, vec3 acceleration, float mass, ofColor color = ofColor::blue,
             float radius = 10, std::string name = "", bool hasTrail = false, float segmentLength = 10.0f,
             int segmentCount = 10)
    {
        this->position = position;
        this->velocity = velocity;
        this->defaultVelocity = velocity;
        this->acceleration = acceleration;
        this->mass = mass;
        this->radius = radius;
        this->color = color;
        this->hasTrail = hasTrail;
        this->trailSegmentLength = segmentCount;
        this->trailSegmentCount = segmentCount;
        this->name = name;
    }

    //Getters
    vec3 getPosition() { return position; }
    vec3 getVelocity() { return velocity; }
    vec3 getDefaultVelocity() { return defaultVelocity; }
    vec3 getAcceleration() { return acceleration; }
    float getMass() { return mass; }
    float getInverseMass() { return 1 / mass; }
    float getRadius() { return radius; }
    ofColor getColor() { return color; }
    std::string getName() { return name; }

    std::string getVelocityAsString() { return std::string(velocity) + "\n"; }
    std::string getAccelerationAsString() { return std::string(acceleration) + "\n"; }
    std::string getPositionAsString() { return std::string(position) + "\n"; }

    //Setters
    void setPosition(vec3 p) { position = p; }
    void setVelocity(vec3 v) { velocity = v; }
    void setAcceleration(vec3 a) { acceleration = a; }
    void setMass(float m) { mass = m; }
    void setRadius(float r) { radius = r; }
    void setColor(ofColor c) { color = c; }
    void setName(std::string n) { name = n; }
    void setDefaultVelocity(vec3 v) { defaultVelocity = v; }

    void update();
    void draw() const;
    void clearTrail();
};
