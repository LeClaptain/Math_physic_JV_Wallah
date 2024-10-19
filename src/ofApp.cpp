#include "ofApp.h"

#include "forces/GravityForceGenerator.h"

vec3 defaultGravity = vec3(0, 9.81 * 50, 0);
//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150, 150, 150, 255);

    //GUI
    setupControlGui();
    setupDebugGui();
    controlGui.setWidthElements(350);

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

    // Setup the scene
    addParticleForce(new Particle(vec3(-20, 100, 0), 1, ofColor::green), new GravityForceGenerator());
    addParticleForce(new Particle(vec3(20, 50, 0), 1, ofColor::red), new GravityForceGenerator());
    addParticleForce(new Particle(vec3(0, 20, 0), 1, ofColor::blue), new GravityForceGenerator());

    collisionDetector.addParticle(particles[0]);
    collisionDetector.addParticle(particles[1]);
    collisionDetector.addParticle(particles[2]);

    particles[0]->setVelocity(vec3(0, 10, 0));
    
    collisionResolver.setElasticity(0.01f);

    camera.setPosition(vec3(0, 0, 500));

    camera.lookAt(vec3(0));
}

void ofApp::addParticleForce(Particle* p, ForceGenerator* generator)
{
    particles.emplace_back(p);
    forces.emplace(generator);
    registry.add(p, generator);
}

void ofApp::addParticle(Particle* p)
{
    particles.emplace_back(p);
}

//--------------------------------------------------------------
void ofApp::update()
{
    double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame

    registry.updateForces(lastFrame);

    auto collisions = collisionDetector.detectAllCollisions();
    collisionResolver.resolveAllCollisions(collisions);

    for (auto& particle : particles)
    {
        particle->update(lastFrame);
        particle->clearForces();
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    //Arrow to symbolize the initial velocity
    drawArrow();

    // Draw scene

    camera.begin();
    ofEnableDepthTest();
    for (const auto& particle : particles)
    {
        particle->draw();
    }
    ofDrawGrid(10.f, 10, false, false, true, false);
    ofDisableDepthTest();
    camera.end();

    //Drawing UI
    controlGui.draw();
    if (isDebugEnabled)
    {
        drawDebugGui();
    }
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
    //Called to specify special angle and velocity for a projectile
    float mousex = ofGetMouseX();
    float mousey = ofGetMouseY();
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
    // positionLabel.setup("Position", activeProjectile->getPositionAsString());
    // velocityLabel.setup("Velocity: ", activeProjectile->getVelocityAsString());
    // accelerationLabel.setup("Acceleration: ", activeProjectile->getAccelerationAsString());
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
    debugGui.add(speedLabel.setup("greenParticleSpeedLabel", ""));

    //Listeners
    fpsLabel.setSize(debugGui.getWidth(), fpsLabel.getHeight());
    frameDurationLabel.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
}

void ofApp::onToggleChanged(bool& value)
{
    isDebugEnabled = value;
}

void ofApp::onResetButtonPressed()
{
}

void ofApp::drawArrow()
{
    /*
    //Initial Velocity Vector
    // if (isLineDrawable)
    // {
    //     ofSetColor(ofColor::blueViolet);
    //     ofSetLineWidth(5);
    //
    //     float textX = initialVelocity.second.x() - 10;
    //     float textY = initialVelocity.second.y() - 15;
    //     std::string vectorIcon = "v";
    //     ofUTF8Append(vectorIcon, 0x20D7);
    //     //ofUTF8Append(vectorIcon,0x2080); // Supposed to be index 0 but not supported by the font
    //
    //     ofDrawArrow(initialVelocity.first, initialVelocity.second, 10.0);
    //     ofSetColor(ofColor::black);
    //
    //     vectorFont.drawString(vectorIcon, textX, textY);
    // }
    */
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
