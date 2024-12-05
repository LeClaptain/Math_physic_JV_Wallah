#include "BoundingVolume.h"
#include <CorpsRigides/CorpsRigide.h>

#include "CorpsRigides/Box.h"
#include "CorpsRigides/Cone.h"
#include "CorpsRigides/Cylinder.h"

BoundingVolume::BoundingVolume(CorpsRigide* rb)
{
	rigidbody = rb;
	center = rb->getPosition();
	if (Box* box = dynamic_cast<Box*>(rigidbody))
	{
		maths::vec3 size = box->getExtent();
		radius = std::max( std::max( size.x(), size.y() ), size.z() );
	}
	else if (Cylinder* cylinder = dynamic_cast<Cylinder*>(rigidbody))
	{
		ofCylinderPrimitive* mesh = cylinder->getRigidBody();
		radius = std::max(mesh->getHeight(), mesh->getRadius());
	}
	else if (Cone* cone = dynamic_cast<Box*>(rigidbody))
	{
		ofConePrimitive* mesh = cylinder->getRigidBody();
		radius = std::max(mesh->getHeight(), mesh->getRadius());
	}
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
