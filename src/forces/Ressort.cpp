#include "Ressort.h"

#include "of3dGraphics.h"
#include "ofxColorPicker.h"


void Ressort::updateForce(Particle* particle, float duration)
{
	float length = (particle->getPosition() - ancre).magnitude();
	vec3 dir = vec3(0, 0, 0);
	if (length != 0.0f)
	{
		dir = (particle->getPosition() - ancre).normalized(); 
	}
	vec3 force = dir * this->springConstant * (restLength - length);
	particle->addForce(force);
}

void Ressort::debugDraw() const
{
	ofSetColor(ofColor::azure);
	ofDrawSphere(ancre, 5);
}
