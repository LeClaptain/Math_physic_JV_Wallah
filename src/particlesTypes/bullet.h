#pragma once
#include "../Particle.h"


class Bullet : public Particle
{

	public:
	Bullet() = default;
	Bullet(vec3 position, vec3 velocity = vec3(-7,-7,0), vec3 acceleration = vec3(0,0,0), float mass = 1.0, 
		ofColor color = ofColor::hotPink, float radius = 10)
	{
		this->setPosition(position);
		this->setVelocity(velocity);
		this->setAcceleration(acceleration);
		this->setMass(mass);
		this->setRadius(radius);
		this->setColor(color);

	};

};