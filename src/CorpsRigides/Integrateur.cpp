#include "Integrateur.h"

#include <iostream>

void Integrateur::integrer(double dt, CorpsRigide* corpsRigide)
{
    //Euler
    corpsRigide->setAcceleration(corpsRigide->getForces() * corpsRigide->getInverseMass());
    corpsRigide->setVelocity(corpsRigide->getVelocity() + corpsRigide->getAcceleration() * dt);
    corpsRigide->setPosition(corpsRigide->getPosition() + corpsRigide->getVelocity() * dt);

    // on calcule le jminusone actuel pour prendre en compte l'orientation
    mat3 orientationMatrix = corpsRigide->getOrientation().toMat3();
    mat3 JminusOnePrim = orientationMatrix * corpsRigide->getJminusOne() * orientationMatrix.inverse();

    // calcul de l'acceleration a partir des forces accumulees dans tau
    corpsRigide->setAngularAcceleration(corpsRigide->getTau() * JminusOnePrim);

    // mise a jour de la velocite puis de l'orientation
    corpsRigide->setAngularVelocity(corpsRigide->getAngularVelocity() + corpsRigide->getAngularAcceleration() * dt);
    corpsRigide->setOrientation(corpsRigide->getOrientation() + quaternion(0, corpsRigide->getAngularVelocity()) * 1.f/2.f * corpsRigide->getOrientation() * dt);
    
    corpsRigide->getRigidBody()->setOrientation(corpsRigide->getOrientation());
    corpsRigide->getRigidBody()->setPosition(corpsRigide->getPosition());

    // reset force accumulation
    corpsRigide->setForces(vec3(0));
    corpsRigide->setTau(vec3(0));
}