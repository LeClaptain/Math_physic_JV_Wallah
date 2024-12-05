#include "BoundingVolume.h"
#include <CorpsRigides/CorpsRigide.h>

#include "CorpsRigides/Box.h"

BoundingVolume::BoundingVolume(CorpsRigide* rb)
{
	rigidbody = rb;
	center = rb->getPosition();
	if (Box* box = dynamic_cast<Box*>(rigidbody))
	{
		maths::vec3 size = box->getExtent();
		radius = std::max( std::max( size.x(), size.y() ), size.z() );
	}
	maths::vec3 size = rb->getExtent();
	radius = std::max( std::max( size.x(), size.y() ), size.z() );
}

void BoundingVolume::draw(ofColor color, int offset)
{
	ofMaterial material;
	ofSpherePrimitive primitive;

	primitive.setRadius(radius + offset);
	primitive.setPosition(center);

	material.setDiffuseColor(color);

	material.begin();
	primitive.draw();
	material.end();
}
