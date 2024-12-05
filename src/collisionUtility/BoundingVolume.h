#pragma once

#include "../maths/vec3.h"
#include "../CorpsRigides/CorpsRigide.h"

class BoundingVolume
{
public:
	BoundingVolume(CorpsRigide* rb);

	BoundingVolume(float size, maths::vec3 position)
	{
		radius = size;
		center = position;
	}

	float getRadius() { return radius; }
	maths::vec3 getCenter() { return center; }
	CorpsRigide* getRigidBody() { return rigidbody; }

	void draw(ofColor color = ofColor(255, 0, 0), int offset = 0);

private:
	float radius;
	maths::vec3 center; // need to update bounding volume center to follow rigidbody
	CorpsRigide* rigidbody;
};

