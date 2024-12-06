#include "BoundingVolume.h"
#include <CorpsRigides/CorpsRigide.h>

#include "CorpsRigides/Box.h"

BoundingVolume::BoundingVolume(CorpsRigide* rb)
{
	rigidbody = rb;
	center = rb->getPosition();
	radius = rb->getContainingRadius();
}

void BoundingVolume::draw(ofColor color)
{
	ofMaterial material;
	ofSpherePrimitive primitive;

	primitive.setRadius(radius);
	primitive.setPosition(center);

	material.setDiffuseColor(color);

	material.begin();
	primitive.draw();
	material.end();
}
