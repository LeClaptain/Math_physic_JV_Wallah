#pragma once
#include "../Particle.h"


class fireBall : public Particle
{

public:
	fireBall(vec3 position, vec3 velocity = vec3(-3, -3, 0), vec3 acceleration = vec3(0, 0, 0), float mass = 1.0,
		ofColor color = ofColor::orangeRed, float radius = 40)
	{
		//Particle::Particle(position, velocity, acceleration, mass, color, radius, "Fireball");
		
		this->setPosition(position);
		this->setVelocity(velocity);
		this->setAcceleration(acceleration);
		this->setMass(mass);
		this->setRadius(radius);
		this->setColor(color);
		this->setName("Fireball");
		this->setDefaultVelocity(velocity);
	};

};