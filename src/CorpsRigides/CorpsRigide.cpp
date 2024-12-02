#include "CorpsRigides/CorpsRigide.h"

#include "ofMaterial.h"
#include "ofxColorPicker.h"

CorpsRigide::CorpsRigide(vec3 position, ofColor color)
{
    this->position = position;
    // this->extent = extent;
    this->color = color;
    setMass(1);
    // rigidBody.set(extent.x(), extent.y(), extent.z());
    calcJminusOne();
}


BoundingVolume* CorpsRigide::generateBoundingVolume()
{
    boundingVolume = new BoundingVolume(this);
    return boundingVolume;
}

void CorpsRigide::applyRotationFromQuaternion() {


    // Appliquer la rotation avec ofRotate
}
