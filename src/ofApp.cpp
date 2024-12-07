#include "ofApp.h"

#include "forces/GravityForceGenerator.h"

#include "forces/TwoParticleSpringForceGenerator.h"
#include "forces/FrictionForceGenerator.h"


vec3 defaultGravity = vec3(0, 9.81 * 50, 0);
//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150, 150, 150, 255);

    //GUI
    setupControlGui();
    setupDebugGui();
    setupFont();

    //SCENE
    setupLight();
    setupThingsToDraw();

    // DEBUG OCTREE DELETE LATER
    
    // octree = new octree::Octree(octree::OTBox(0.0f, 0.0f, 0.0f, 1000.0f, 1000.0f, 1000.0f));
    // for (int i = 0; i < 100; i++)
    // {
    //     auto position = maths::vec3((std::rand() % 1000) - 500, (std::rand() % 1000) - 500, (std::rand() % 1000) - 500);
    //     
    //     octree->add(new BoundingVolume(5.0f, position));
    // }

    camera.setPosition(vec3(0, 0, 500));
    camera.setFarClip(10000.0f);
    camera.lookAt(vec3(0));

    // collisionDetector.setDebug(true);
}

//--------------------------------------------------------------
void ofApp::update()
{
    double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame
    Integrateur integrateur = Integrateur();
    
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
    //Arrow to symbolize the initial velocity
    // drawArrow();

    light.enable();

    // Draw scene
    camera.begin();
    ofEnableDepthTest();
    for (const auto& corps : rigidBodies)
    {
        corps->draw();

        // ofDrawSphere(corps->getPosition(), corps->getContainingRadius());
    }

    // DEBUG OCTREE DELETE LATER
    
    // octree->draw();
    // octree::OTBox queryBox(maths::vec3(125.0f, 125.0f, 125.0f), maths::vec3(300.0f));
    // queryBox.draw();
    // auto values = octree->query(queryBox);
    // if (!values.empty())
    // {
    //     for (auto& value : values)
    //     {
    //         value->draw(ofColor(255, 255, 255), 5);
    //     }
    // }

    

    auto collisions = collisionDetector.FindAllCollisions();
    for (auto& collision : collisions)
    {
        // std::cout << "Collision detected between " << collision.body1 << " and " << collision.body2 << std::endl;
        for (auto& point : collision.collisionPoints)
        {
            ofDrawSphere(point.point, 5.f);
        }
    }

    ofDrawGrid(25.f, 1000, false, false, true, false);
    ofDisableDepthTest();

    camera.end();

    //Drawing UI

    controlGui.draw();
    // if (isDebugEnabled)
    // {
    //     drawDebugGui();
    // }
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
    // if F key
    if (key == 102)
    {
        for (auto rb : rigidBodies)
        {
            rb->addForce(vec3(0, 500, 0), vec3(1, 1, 1));
        }
    }
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
    controlGui.add(resetButton.setup("Reset the scene"));
    //controlGui.add(debugToggle.setup("Debug Toggle", false));
    controlGui.add(changeProjectileButton.setup("Change Projectile"));
    controlGui.add(launchProjectileButton.setup("Launch Projectile"));
    
    //Listeners
    resetButton.addListener(this, &ofApp::onResetButtonPressed);
    changeProjectileButton.addListener(this, &ofApp::onChangeProjectilePressed);
    launchProjectileButton.addListener(this, &ofApp::onLaunchProjectilePressed);
}

void ofApp::setupDebugGui()
{
    //Placements
    debugGui.setup();
    debugGui.setDefaultWidth(400);
    debugGui.setWidthElements(400);
    debugGui.add(fpsLabel.setup("fpsLabel", ""));
    debugGui.add(frameDurationLabel.setup("frameDurationLabel", ""));
    debugGui.add(blobNumberLabel.setup("blobNumberLabel", ""));

    //debugGui.add(particlePosition.setup("Particle Position", ""));
    //debugGui.add(particleVelocity.setup("Particle Velocity", ""));
    //debugGui.add(speedLabel.setup("greenParticleSpeedLabel", ""));

    //Listeners
    fpsLabel.setSize(debugGui.getWidth(), fpsLabel.getHeight());
    frameDurationLabel.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
    particlePosition.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
    particleVelocity.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
}

void ofApp::setupFont()
{
    //Font related shenaningans for displaying vectors
    string path = ofFilePath::getEnclosingDirectory(ofFilePath::getCurrentWorkingDirectory()) +
        "src/externalressources/Fonts/LatinModern.otf";
    // TODO : find a font that supports both characters mentioned bellow
    ofTrueTypeFontSettings settings(path, 32);
    ofUnicode::range vectorArrow(0x20D7, 0x20D7); //adds the unicode character for a vector
    ofUnicode::range underZero(0x2080, 0x2089); //adds the unicode charactor for all numbers as indexes
    settings.addRange(vectorArrow);
    settings.addRange(underZero);
    settings.addRanges(ofAlphabet::Latin);
    vectorFont.load(settings);
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
    Box* sol = new Box(vec3(1000, 100, 1000), vec3(0,-50,0), ofColor::lightGray);
    rigidBodies.push_back(sol);
    Box* mur1 = new Box(vec3(1000, 400, 1), vec3(0, 200, 500), ofColor::lightGray);
    rigidBodies.push_back(mur1);
    Box* mur2 = new Box(vec3(1000, 400, 1), vec3(0, 200, -500), ofColor::lightGray);
    rigidBodies.push_back(mur2);
    Box* mur3 = new Box(vec3(1, 400, 1000), vec3(500, 200, 0), ofColor::lightGray);
    rigidBodies.push_back(mur3);
    Box* mur4 = new Box(vec3(1, 400, 1000), vec3(-500, 200, 0), ofColor::lightGray);
    rigidBodies.push_back(mur4);
    Box* plafond = new Box(vec3(1000, 1, 1000), vec3(0,400,0), ofColor::lightGray);
    rigidBodies.push_back(plafond);

    //Trucs a placer dans la scène
    Box* cube2 = new Box(vec3(50, 50, 50), vec3(-100,0,0), ofColor::green);
    rigidBodies.push_back(cube2);

    collisionDetector.addBody(cube2);
    collisionDetector.addBody(sol);
    collisionDetector.addBody(mur1);
    collisionDetector.addBody(mur2);
    collisionDetector.addBody(mur3);
    collisionDetector.addBody(mur4);
    collisionDetector.addBody(plafond);
}

void ofApp::onToggleChanged(bool& value)
{
    isDebugEnabled = value;
}

void ofApp::onResetButtonPressed()
{
    CorpsRigide* rigidBody = rigidBodies[0];
    rigidBody->setVelocity(vec3(0, 0, 0));
    rigidBody->setAngularVelocity(vec3(0, 0, 0));
    rigidBody->setPosition(vec3(0, 50, 0));
    rigidBody->setOrientation(quaternion(0, vec3(0, 50, 0)));
}

 void ofApp::onChangeProjectilePressed()
 {
//     CorpsRigide* rigidBody = rigidBodies[0];
//     rigidBody->setVelocity(vec3(0, 0, 0));
//     rigidBody->setAngularVelocity(vec3(0, 0, 0));
//     rigidBody->setPosition(vec3(0, 50, 0));
//     rigidBody->setOrientation(quaternion(0, vec3(0, 50, 0)));
//     currentRigidBody = (currentRigidBody + 1) % RigidBodiesChoice.size();
//     rigidBodies.clear();
//     rigidBodies.emplace_back(RigidBodiesChoice[currentRigidBody]);
 }
void ofApp::onLaunchProjectilePressed()
{
    CorpsRigide* rigidBody = rigidBodies[0];
    // rigidBody->setVelocity(vec3(50, 50, 20));
    // rigidBody->setAngularVelocity(vec3(1000, 1000, 0));
    rigidBody->addForce(vec3(5000, 0, 0), vec3(10,100,0));
}


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
