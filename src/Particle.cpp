﻿#include "Particle.h"

#include "of3dGraphics.h"
#include "ofAppRunner.h"
#include "ofGraphics.h"

void Particle::update(double dt)
{
	//Euler Integration
	acceleration = forces * oneOverMass;
	velocity += acceleration*dt;
	this->position += velocity*dt;

	// Update trail

	if (hasTrail)
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
	// ofDrawSphere(position, radius + 2);
	ofSetColor(color);
	ofDrawSphere(position, radius);
}

void Particle::clearTrail()
{
	segmentPoints = {};
}
