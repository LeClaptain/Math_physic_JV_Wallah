#pragma once

#include "../maths/vec3.h"
#include "../CorpsRigide.h"

class BoundingVolume
{
public:
	BoundingVolume(CorpsRigide* rb);

	float getRadius() { return radius; }
	maths::vec3 getCenter() { return center; }
	CorpsRigide* getRigidBody() { return rigidbody; }

private:
	float radius;
	maths::vec3 center; // need to update bounding volume center to follow rigidbody
	CorpsRigide* rigidbody;
};

