#include "ofApp.h"

vec3 defaultGravity = vec3(0, 9.81 * 50, 0);
//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150, 150, 150, 255);
    initialVelocity.first = maths::vec3(ofGetWidth(), ofGetHeight(), 0); //bottom left corner
    setupProjecticles();

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
}

//--------------------------------------------------------------
void ofApp::update()
{
    //double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame

    //Update only if the active projectile is still visible
    if (activeProjectile->getPosition().y() >= ofGetHeight() + activeProjectile->getRadius() ||
        activeProjectile->getPosition().x() <= 0 - activeProjectile->getRadius())
    {
        activeProjectile->setPosition(vec3(ofGetWidth(), ofGetHeight(), 0));
        activeProjectile->setVelocity(vec3());
        activeProjectile->setAcceleration(vec3());
        isParticleMoovable = false;
    }
    if (!isParticleMoovable) { return; }

    activeProjectile->update();
}

//--------------------------------------------------------------
void ofApp::draw()
{
    activeProjectile->draw();

    //Arrow to symbolize the initial velocity
    drawArrow();

    //Drawing UI
    controlGui.draw();
    if (isDebugEnabled)
    {
        drawDebugGui();
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

    //In case the mouse is used before the last movement ends
    activeProjectile->setPosition(vec3(ofGetWidth(), ofGetHeight(), 0));
    activeProjectile->clearTrail();
    
    activeProjectile->setVelocity(maths::vec3(mousex - ofGetWidth(), mousey - ofGetHeight(), 0));
    activeProjectile->setAcceleration(defaultGravity);

    initialVelocity.second = maths::vec3(mousex, mousey, 0);
    isLineDrawable = true;
    isParticleMoovable = true;
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
    //Resets the scene when the window is resized
    initialVelocity.first = maths::vec3(ofGetWidth(), ofGetHeight(), 0);
    activeProjectile->setPosition(vec3(ofGetWidth(), ofGetHeight(), 0));
    activeProjectile->clearTrail();

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
    positionLabel.setup("Position", activeProjectile->getPositionAsString());
    velocityLabel.setup("Velocity: ", activeProjectile->getVelocityAsString());
    accelerationLabel.setup("Acceleration: ", activeProjectile->getAccelerationAsString());
}

void ofApp::setupControlGui()
{
    //Placements
    controlGui.setup();
    controlGui.setDefaultWidth(350);
    controlGui.setWidthElements(350);
    controlGui.setPosition(10, ofGetHeight() - 120);
    controlGui.add(nextProjectileLabel.setup("Next projectile", activeProjectile->getName()));
    controlGui.add(launchButton.setup("Launch projectile"));
    controlGui.add(nextProjectileButton.setup("Next projectile"));
    controlGui.add(resetButton.setup("Reset the scene"));
    controlGui.add(debugToggle.setup("Debug Toggle", false));

    //Listeners
    launchButton.addListener(this, &ofApp::onLaunchButtonPressed);
    nextProjectileButton.addListener(this, &ofApp::onNextProjectileButtonPressed);
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
    debugGui.add(positionLabel.setup("positionLabel", ""));
    debugGui.add(velocityLabel.setup("velocityLabel", ""));
    debugGui.add(accelerationLabel.setup("accelerationLabel", ""));

    //Listeners
    fpsLabel.setSize(debugGui.getWidth(), fpsLabel.getHeight());
    frameDurationLabel.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
    positionLabel.setSize(debugGui.getWidth(), positionLabel.getHeight());
    velocityLabel.setSize(debugGui.getWidth(), velocityLabel.getHeight());
    accelerationLabel.setSize(debugGui.getWidth(), accelerationLabel.getHeight());
}

void ofApp::setupProjecticles()
{
    //Initializes the list of projectiles
    projectiles.push_back(new Particle(maths::vec3(0, 0, 0), maths::vec3(-500, -500, 0), maths::vec3()
                                       , 0.0, ofColor::blue, 30, "Particle", true, 10, 0));
    projectiles.push_back(new Bullet(vec3(), vec3(-700, -700, 0)));
    projectiles.push_back(new canonBall(vec3(), vec3(-300, -700, 0)));
    projectiles.push_back(new fireBall(vec3(), vec3(-1000, -300, 0)));

    activeProjectile = projectiles[0];
    activeProjectile->setPosition(maths::vec3(ofGetWidth(), ofGetHeight(), 0));
}


void ofApp::onToggleChanged(bool& value)
{
    isDebugEnabled = value;
}

void ofApp::onNextProjectileButtonPressed()
{
    //cycles through the projectile list
    activeProjectile->setVelocity(vec3());
    activeProjectile->setAcceleration(vec3());
    activeProjectile->clearTrail();

    string nameLastProjectile = activeProjectile->getName();
    if (nameLastProjectile == "Particle")
    {
        activeProjectile = projectiles[1];
    }
    else if (nameLastProjectile == "Bullet")
    {
        activeProjectile = projectiles[2];
    }
    else if (nameLastProjectile == "Canonball")
    {
        activeProjectile = projectiles[3];
    }
    else if (nameLastProjectile == "Fireball")
    {
        activeProjectile = projectiles[0];
    }
    activeProjectile->setPosition(maths::vec3(ofGetWidth(), ofGetHeight(), 0));

    nextProjectileLabel.setup("Next projectile", activeProjectile->getName());
    nextProjectileLabel.setSize(controlGui.getWidth(), nextProjectileLabel.getHeight());
}

void ofApp::onLaunchButtonPressed()
{
    isParticleMoovable = true;
    
    //In case the last movement didn't end
    activeProjectile->setPosition(vec3(ofGetWidth(), ofGetHeight(), 0)); 
    activeProjectile->clearTrail();
    
    activeProjectile->setVelocity(activeProjectile->getDefaultVelocity());
    activeProjectile->setAcceleration(defaultGravity);
}

void ofApp::onResetButtonPressed()
{
    isLineDrawable = false;
    activeProjectile->clearTrail();
    activeProjectile->setPosition(vec3(ofGetWidth(), ofGetHeight(), 0));
}

void ofApp::drawArrow()
{
    //Initial Velocity Vector
    if (isLineDrawable)
    {
        ofSetColor(ofColor::blueViolet);
        ofSetLineWidth(5);

        float textX = initialVelocity.second.x() - 10;
        float textY = initialVelocity.second.y() - 15;
        std::string vectorIcon = "v";
        ofUTF8Append(vectorIcon, 0x20D7);
        //ofUTF8Append(vectorIcon,0x2080); // Supposed to be index 0 but not supported by the font

        ofDrawArrow(initialVelocity.first, initialVelocity.second, 10.0);
        ofSetColor(ofColor::black);

        vectorFont.drawString(vectorIcon, textX, textY);
    }
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
}
