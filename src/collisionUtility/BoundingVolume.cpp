#include "BoundingVolume.h"

BoundingVolume::BoundingVolume(CorpsRigide* rb)
{
	rigidbody = rb;
	center = rb->getPosition();
	maths::vec3 size = rb->getExtent();
	radius = std::max( std::max( size.x(), size.y() ), size.z() );
}
