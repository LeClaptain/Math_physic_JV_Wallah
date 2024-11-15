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

    setupThingsToDraw();

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
    /*
    controlGui.draw();
    if (isDebugEnabled)
    {
        drawDebugGui();
    }*/
    light.disable();
}

ofApp::~ofApp()
{
    for (auto particle : particles)
    {
        delete particle;
    }
    for (auto force : forces)
    {
        delete force;
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    //ajouter de la vitesse à la première particule de la liste blob
    if (key == OF_KEY_UP)
    {
        blob[0]->setVelocity(vec3(0, 0, -100));
    }
    if (key == OF_KEY_DOWN)
    {
        blob[0]->setVelocity(vec3(0, 0, 100));
    }
    if (key == OF_KEY_LEFT)
    {
        blob[0]->setVelocity(vec3(-100, 0, 0));
    }
    if (key == OF_KEY_RIGHT)
    {
        blob[0]->setVelocity(vec3(100, 0, 0));
    }

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
    if (button != OF_MOUSE_BUTTON_RIGHT)
    {
        return;
    }

    Particle* selected = nullptr;
    for (auto particle : particles)
    {
        vec3 particleScreenPos = camera.worldToScreen(particle->getPosition());
        vec3 outerPointScreenPos = camera.worldToScreen(particle->getPosition() + vec3(particle->getRadius(), 0, 0));
        float onScreenRadius = outerPointScreenPos.distance(particleScreenPos);

        if (particleScreenPos.distance(vec3(x, y, 0)) < onScreenRadius)
        {
            selected = particle;
            break;
        }
    }
    selectedParticle = selected;
    if (selectedParticle != nullptr)
    {
        vec3 particlePos = selectedParticle->getPosition();
        selectionPlaneNormal = camera.getLookAtDir() * -1;
        selectionPlanePoint = particlePos;
        camera.disableMouseInput();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    if (button == OF_MOUSE_BUTTON_RIGHT)
    {
        selectedParticle = nullptr;
        camera.enableMouseInput();
    }
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
    blobNumberLabel.setup("Number of blob particules", std::to_string(blob.size()));
}

void ofApp::setupControlGui()
{
    //Placements
    controlGui.setup();
    controlGui.setDefaultWidth(350);
    controlGui.setWidthElements(350);
    controlGui.setPosition(10, ofGetHeight() - 120);
    // controlGui.add(nextProjectileLabel.setup("Next projectile", activeProjectile->getName()));
    //controlGui.add(resetButton.setup("Reset the scene"));
    controlGui.add(debugToggle.setup("Debug Toggle", false));

    //Listeners
    resetButton.addListener(this, &ofApp::onResetButtonPressed);
    debugToggle.addListener(this, &ofApp::onToggleChanged);
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
    CorpsRigide* cube1 = new CorpsRigide(vec3(0, 50, 0), vec3(100, 50, 50), ofColor::red);
    //DEBUG
    // cube1->setOrientation(quaternion(0.5, 1,0,0));
    // cube1->setAngularVelocity(vec3(0,5,0));
    cube1->addForce(vec3(500, 0, 0), vec3(1, 1, 1));

    rigidBodies.emplace_back(cube1);
}

void ofApp::onToggleChanged(bool& value)
{
    isDebugEnabled = value;
}

void ofApp::onResetButtonPressed()
{
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
