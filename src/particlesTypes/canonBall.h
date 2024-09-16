#pragma once
#include "../Particle.h"


class canonBall : public Particle
{

public:
	canonBall() = default;
	canonBall(vec3 position, vec3 velocity = vec3(-10, -7, 0), vec3 acceleration = vec3(0, 0, 0), float mass = 10.0,
		ofColor color = ofColor::black, float radius = 50)
	{
		this->setPosition(position);
		this->setVelocity(velocity);
		this->setAcceleration(acceleration);
		this->setMass(mass);
		this->setRadius(radius);
		this->setColor(color);

	};

};