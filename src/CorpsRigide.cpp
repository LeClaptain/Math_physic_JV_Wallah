#include "CorpsRigide.h"

#include "ofxColorPicker.h"

CorpsRigide::CorpsRigide(vec3 position, vec3 extent, ofColor color)
{
    this->position = position;
    this->extent = extent;
    this->color = color;
    rigidBody.set(extent.x() * 2, extent.y() * 2, extent.z() * 2);
}

void CorpsRigide::update(double dt)
{
    //Euler
    acceleration = forces * inverseMass;
    velocity = velocity + acceleration * dt;
    this->position += velocity * dt;
    
}

void CorpsRigide::draw()
{
    ofSetColor(color);
    rigidBody.setPosition(position);
    //rigidBody.setPosition(ofGetWidth() / 2, ofGetHeight() / 2, 0);
    rigidBody.draw();
    //rigidBody.drawWireframe();
}
