#include "Particle.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"

void Particle::update()
{
	double dt = ofGetLastFrameTime();
	this->position += velocity;
	velocity += acceleration * dt;

	// Update trail if still in view
	if (position.y() >= ofGetHeight()+ radius || position.y() <= 0- radius)
	{
		position = {-100,-100,0};
		velocity = {0,0,0};
		acceleration = {0,0,0};
	}
	else if (hasTrail)
	{
		if (segmentPoints.empty())
		{
			segmentPoints.push_front(position);
		}

		if (segmentPoints.front().distance(position) >= trailSegmentLength)
		{
			segmentPoints.push_front(position);
		}

		while (trailSegmentCount != 0 && segmentPoints.size() > trailSegmentCount)
		{
			segmentPoints.pop_back();
		}
	}


}

void Particle::draw() const
{
	// vec3 cross = velocity.cross(vec3(0, 0, 1)).normalized();

	// ofSetColor(ofColor::white);
	// ofDrawTriangle(position - cross * radius, position + cross * radius, position - velocity * trailSegmentLength);
	
	ofSetColor(ofColor::red);
	ofSetLineWidth(2);
	if (hasTrail)
	{
		for (int i = 1; i < segmentPoints.size(); i++)
		{
			ofDrawLine(segmentPoints[i - 1], segmentPoints[i]);
		}
	}

	ofSetColor(ofColor::black);
	ofDrawCircle(position, radius + 2);
	ofSetColor(color);
	ofDrawCircle(position, radius);
}

void Particle::clearTrail()
{
	segmentPoints = {};
}
