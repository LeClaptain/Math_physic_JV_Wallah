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
    setupLight();

    // différents corps rigides
    CorpsRigide* cube0 = new CorpsRigide(vec3(0, 50, 0), vec3(100, 50, 50), ofColor::red);
    CorpsRigide* cube1 = new CorpsRigide(vec3(0, 50, 0), vec3(75, 20, 40), ofColor::blueSteel);
    CorpsRigide* cube2 = new CorpsRigide(vec3(0, 50, 0), vec3(50, 50, 50), ofColor::green);
    rigidBodies.push_back(cube0);
    rigidBodies.push_back(cube1);
    rigidBodies.push_back(cube2);

    camera.setPosition(vec3(0, 0, 500));
    camera.setFarClip(10000.0f);
    camera.lookAt(vec3(0));
}

//--------------------------------------------------------------
void ofApp::update()
{
    double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame


    // euler integration
    for (auto& CorpsRigide : rigidBodies)
    {
        CorpsRigide->update(lastFrame);
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
    for (const auto& CorpsRigide : rigidBodies)
    {
        CorpsRigide->draw();
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


//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
