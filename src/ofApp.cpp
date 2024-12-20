#include "ofApp.h"

#include "forces/GravityForceGenerator.h"

#include "forces/TwoParticleSpringForceGenerator.h"
#include "forces/FrictionForceGenerator.h"
#include "collisionUtility/GeneralCollisionSolver.h"


vec3 defaultGravity = vec3(0, 9.81 * 50, 0);
//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150, 150, 150, 255);

    //GUI
    setupControlGui();
    setupDebugGui();

    //SCENE
    setupLight();
    setupThingsToDraw();

    camera.setPosition(vec3(0, 0, 500));
    camera.setFarClip(10000.0f);
    camera.lookAt(vec3(0));

    collisionSolver.setElasticity(0.01f);
}

//--------------------------------------------------------------
void ofApp::update()
{
    double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame
    Integrateur integrateur = Integrateur();
    integrateur.setDamping(0.1f);

    // gravity hack
    for (auto& corpsRigide : gravityAffectedBodies)
    {
        corpsRigide->addForce(vec3(0, -9.81f * 8.f * corpsRigide->getMass(), 0));
    }

    // resolve collisions
    std::vector<CollisionPair> collisions = collisionDetector.FindAllCollisions();
    collisionSolver.ResolveCollisions(collisions);

    // euler integration
    for (auto& CorpsRigide : rigidBodies)
    {
        // CorpsRigide->update(lastFrame);
        integrateur.integrer(lastFrame, CorpsRigide);
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    light.enable();

    // Draw scene
    camera.begin();
    ofEnableDepthTest();

    for (const auto& corps : rigidBodies)
    {
        corps->draw();
    }

    ofDrawGrid(25.f, 1000, false, false, true, false);
    

    // Ugly but it's because we can't copy an octree due to the way it's implemented (and we dont have time to fix it)
    if (drawOctree)
    {
        auto otbox = octree::OTBox(maths::vec3(0, 200, 0), maths::vec3(3000));
        octree::Octree o = octree::Octree(otbox);
        std::vector<BoundingVolume*> volumes;

        for (auto& body : rigidBodies)
        {
            // TOO LATE BUT SHOULDNT HAVE USED POINTERS HERE
            // Can cause memory leaks, isn't optimal cause we dont need pointers later on, etc
            volumes.push_back(new BoundingVolume(body));
            o.add(volumes.back());
        }

        o.draw();

        // Fix memory leak
        for (auto volume : volumes)
        {
            delete volume;
        }
    }
    
    ofDisableDepthTest();

    camera.end();

    //Drawing UI
    controlGui.draw();

    if (isDebugEnabled)
    {
        drawDebugGui();
    }

    light.disable();
}

ofApp::~ofApp()
{
    for (auto rb : rigidBodies)
    {
        delete rb;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    controlGui.setPosition(10, ofGetHeight() - 120);
    debugGui.setPosition(10, 10);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
}

void ofApp::drawDebugGui()
{
    debugGui.draw();
    fpsLabel.setup("FPS", std::to_string(ofGetFrameRate()));
    frameDurationLabel.setup("Frame Duration", std::to_string(ofGetLastFrameTime() * 1000) + " ms");
}

void ofApp::setupControlGui()
{
    //Placements
    controlGui.setup();
    controlGui.setDefaultWidth(350);
    controlGui.setWidthElements(350);
    controlGui.setPosition(10, ofGetHeight() - 120);
    // controlGui.add(nextProjectileLabel.setup("Next projectile", activeProjectile->getName()));
    controlGui.add(resetButton.setup("Reset green block"));
    controlGui.add(launchProjectileButton.setup("Launch green block"));
    controlGui.add(debugToggle.setup("Debug Toggle", false));
    controlGui.add(drawOctreeToggle.setup("Draw Octree", false));

    //Listeners
    resetButton.addListener(this, &ofApp::onResetButtonPressed);
    launchProjectileButton.addListener(this, &ofApp::onLaunchProjectilePressed);
    debugToggle.addListener(this, &ofApp::onToggleDebug);
    drawOctreeToggle.addListener(this, &ofApp::onToggleDrawOctree);
}

void ofApp::setupDebugGui()
{
    //Placements
    debugGui.setup();
    debugGui.setDefaultWidth(400);
    debugGui.setWidthElements(400);
    debugGui.add(fpsLabel.setup("fpsLabel", ""));
    debugGui.add(frameDurationLabel.setup("frameDurationLabel", ""));

    //Listeners
    fpsLabel.setSize(debugGui.getWidth(), fpsLabel.getHeight());
    frameDurationLabel.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
}

void ofApp::setupLight()
{
    light.setDirectional();
    light.setPosition(0, 0, 500);
    light.setOrientation(vec3(45, -45, 0));
    light.setAmbientColor(ofColor(255, 255, 255));
    light.setDiffuseColor(ofColor(255, 255, 255));
    light.setSpecularColor(ofColor(255, 255, 255));
}

void ofApp::setupThingsToDraw()
{
    // mise en place de la scène (murs, sol et plafond)
    Box* sol = new Box(vec3(1500, 100, 1500), vec3(0, -50, 0), ofColor::lightGray);
    sol->setUnmoovable(true);
    rigidBodies.push_back(sol);
    Box* mur1 = new Box(vec3(1000, 500, 50), vec3(0, 200, 500), ofColor::lightGray);
    mur1->setUnmoovable(true);
    rigidBodies.push_back(mur1);
    Box* mur2 = new Box(vec3(1000, 500, 50), vec3(0, 200, -500), ofColor::lightGray);
    mur2->setUnmoovable(true);
    rigidBodies.push_back(mur2);
    Box* mur3 = new Box(vec3(50, 500, 1000), vec3(500, 200, 0), ofColor::lightGray);
    mur3->setUnmoovable(true);
    rigidBodies.push_back(mur3);
    Box* mur4 = new Box(vec3(50, 500, 1000), vec3(-500, 200, 0), ofColor::lightGray);
    mur4->setUnmoovable(true);
    rigidBodies.push_back(mur4);
    // Box* plafond = new Box(vec3(1000, 50, 1000), vec3(0, 400, 0), ofColor::lightGray);
    // plafond->setUnmoovable(true);
    // rigidBodies.push_back(plafond);

    //Trucs a placer dans la scène
    Box* cube2 = new Box(vec3(50, 50, 50), vec3(0, 200, 0), ofColor::green);
    Box* cube3 = new Box(vec3(20, 40, 20), vec3(0, 400, 0), ofColor::red);
    rigidBodies.push_back(cube3);
    rigidBodies.push_back(cube2);
    // cube2->setMass(10.0f);
    // cube3->setMass(1.0f);

    gravityAffectedBodies.push_back(cube2);
    gravityAffectedBodies.push_back(cube3);

    collisionDetector.addBody(sol);
    collisionDetector.addBody(mur1);
    collisionDetector.addBody(mur2);
    collisionDetector.addBody(mur3);
    collisionDetector.addBody(mur4);
    // collisionDetector.addBody(plafond);
    collisionDetector.addBody(cube2);
    collisionDetector.addBody(cube3);
}

void ofApp::onToggleDebug(bool& value)
{
    isDebugEnabled = value;
}

void ofApp::onToggleDrawOctree(bool& value)
{
    drawOctree = value;
}

void ofApp::onResetButtonPressed()
{
    CorpsRigide* rigidBody = rigidBodies.back();
    rigidBody->setVelocity(vec3(0, 0, 0));
    rigidBody->setAngularVelocity(vec3(0, 0, 0));
    rigidBody->setPosition(vec3(0, 400, 0));
    rigidBody->setOrientation(quaternion(0, vec3(.5, .5, 0)));
}

void ofApp::onLaunchProjectilePressed()
{
    rigidBodies.back()->addForce(vec3(0, 2000, 2000) * rigidBodies.back()->getMass(),
                                 rigidBodies.back()->getPosition() + vec3(0, 0, 10));
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
