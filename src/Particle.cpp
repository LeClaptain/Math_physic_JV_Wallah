#include "Particle.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"

void Particle::update(){
    
    double dt = ofGetLastFrameTime();
    this->position += velocity;
    velocity += acceleration * dt;
}

void Particle::draw() const{
    ofSetColor(ofColor::black);
    ofDrawCircle(position, radius+2);
    ofSetColor(color);
    ofDrawCircle(position, radius);
}
