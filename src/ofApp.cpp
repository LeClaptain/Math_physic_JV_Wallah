#include "ofApp.h"

#include "forces/GravityForceGenerator.h"

#include "forces/TwoParticleSpringForceGenerator.h"
#include "forces/FrictionForceGenerator.h"
#include "forces/RodForceGenerator.h"
#include "forces/Ressort1.h"
#include "forces/Bungee.h"


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

    /*addParticle(new Particle(vec3(30, 0, 30), 0, 0, 1, ofColor::blue));
    addParticle(new Particle(vec3(-30, 0, -30), 0, 0, 1, ofColor::red));
    addParticleForce(particles[0], new GravityForceGenerator());
    addParticleForce(particles[1], new GravityForceGenerator());
    addParticleForce(particles[0], new FrictionForceGenerator(2, 0.03));
    addParticleForce(particles[1], new FrictionForceGenerator(2, 0.03));
    addParticleForce(particles[0], new RodForceGenerator(particles[0], particles[1]));
    addParticleForce(particles[1], forces[forces.size()-1]);*/
    /*addParticleForce(new Particle(vec3(0, 20, 0), 0, 0, 1, ofColor::blue), new GravityForceGenerator());
    addParticleForce(new Particle(vec3(0, 10, 0), 0, 0, 1, ofColor::red), new GravityForceGenerator());
    addParticle(new Particle(vec3(0, 0, 0), 0, 0, 10000000000.f, ofColor::green));

    collisionSolver.addParticle(particles[0]);
    collisionSolver.addParticle(particles[1]);
    collisionSolver.addParticle(particles[2]);*/
    // Create particles and add them to the vector
    
    //basics
    Particle* basic1 = new Particle(vec3(-19, 100, 0), 2, ofColor::green);
    addParticle(basic1);
    Particle* basic2 = new Particle(vec3(20, 80, 0), 2, ofColor::red);
    addParticle(basic2);
    Particle * basic3 = new Particle(vec3(0, 20, 0), 1, ofColor::blue);
    addParticle(basic3);

    //Springs
    Particle* spring1 = new Particle(vec3(80, 20, 0), 2, ofColor::blue);
    addParticle(spring1);

    //Bungee
    Particle* bungee1 = new Particle(vec3(50, 100, 0), 3, ofColor::pink);
    addParticle(bungee1);
    Particle* bungee2 = new Particle(vec3(100, 250, 0), 3, ofColor::black);
    addParticle(bungee2);

    //Rod
    Particle* rod1 = new Particle(vec3(-50, 100, 0), 3, ofColor::purple);
    Particle* rod2 = new Particle(vec3(-100, 100, 0), 3, ofColor::purple);
    addParticle(rod2);
    addParticle(rod1);
    addParticleForce(particles[0], new RodForceGenerator(particles[0], particles[1]));

    //Double Spring
    Particle* dSpring1 = new Particle(vec3(-150, 100, 0), 3, ofColor::orangeRed);
    Particle* dSpring2 = new Particle(vec3(-200, 100, 0), 3, ofColor::yellow);
    addParticle(dSpring1);
    addParticle(dSpring2);
    TwoParticleSpringForceGenerator * twoSideSpring = new TwoParticleSpringForceGenerator(dSpring1, dSpring2, 3, 50);
    addParticleForce(dSpring1, twoSideSpring);
    addParticleForce(dSpring2, twoSideSpring);
    
    // Add gravity and track their collisions
    addGravityToParticles();
    setDetectorList();

    //add other forces
    addParticleForce(spring1, new Ressort1(2, 50, spring1, vec3(0, 80, 0)));
    addParticleForce(bungee1, new Bungee(2, 150, bungee1, bungee2));
    //addParticleForce(bungee2, new Bungee(2, 150, bungee2, bungee1));
    addParticleForce(rod1, new RodForceGenerator(rod1, rod2));

    
    /*addParticleForce(new Particle(vec3(-19, 100, 0), 1, ofColor::green), new GravityForceGenerator());
    addParticleForce(new Particle(vec3(20, 50, 0), 1, ofColor::red), new GravityForceGenerator());
    addParticleForce(new Particle(vec3(0, 20, 0), 1, ofColor::blue), new GravityForceGenerator());

    Particle* visuAncre = new Particle(vec3(0, 80, 0), 1, ofColor::red);
    addParticle(visuAncre);
    Particle* particle = new Particle(vec3(50, 30, 0), 1, ofColor::black);
    addParticleForce(particle, new Ressort1(2, 50, particle, vec3(0, 80, 0)));
    addParticleForce(particle, new GravityForceGenerator());*/

    /*Particle* bungeeParticle1 = new Particle(vec3(-50, 100, 0), 1, ofColor::red);
    Particle* bungeeParticle2 = new Particle(vec3(50, 100, 0), 1, ofColor::black);
    addParticleForce(bungeeParticle1, new Bungee(10, 50, bungeeParticle1, bungeeParticle2));
    addParticleForce(bungeeParticle2, new Bungee(10, 50, bungeeParticle2, bungeeParticle1));*/

    
    collisionResolver.setElasticity(0.5f);
    camera.setPosition(vec3(0, 0, 500));

    camera.lookAt(vec3(0));
}

void ofApp::addParticleForce(Particle* p, ForceGenerator* generator)
{
    //particles.emplace_back(p);
    forces.emplace_back(generator);
    registry.add(p, generator);
}

void ofApp::addParticle(Particle* p)
{
    particles.emplace_back(p);
}

void ofApp::setDetectorList()
{
    for (auto& particle : particles)
    {
        collisionDetector.addParticle(particle);
    }
}

void ofApp::addGravityToParticles()
{
    for (auto& particle : particles)
    {
        addParticleForce(particle, new GravityForceGenerator());
    }
}

void ofApp::addFrictionToParticles()
{
    for (auto& particle : particles)
    {
        addParticleForce(particle, new FrictionForceGenerator(5, 0.03));
    }
}

//--------------------------------------------------------------
void ofApp::update()
{
    double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame

    // Add forces applied by mouse
    if (selectedParticle != nullptr)
    {
        // Find intersection between mouse ray and selection plane
        vec3 rayOrigin = camera.screenToWorld(vec3(ofGetMouseX(), ofGetMouseY(), 0));
        vec3 rayDirection = (vec3(camera.screenToWorld(vec3(ofGetMouseX(), ofGetMouseY(), 1))) - rayOrigin).normalize();
        float t = (selectionPlanePoint - rayOrigin).dot(selectionPlaneNormal) / rayDirection.dot(selectionPlaneNormal);
        vec3 intersection = rayOrigin + rayDirection * t;

        vec3 force = (intersection - selectedParticle->getPosition()) * 100;
        
        selectedParticle->addForce(force);
    }

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
    particlePosition.setup("Particle Position", particles[0]->getPositionAsString());
    particleVelocity.setup("Particle Velocity", particles[0]->getVelocityAsString());
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
    debugGui.add(particlePosition.setup("Particle Position", ""));
    debugGui.add(particleVelocity.setup("Particle Velocity", ""));
    debugGui.add(speedLabel.setup("greenParticleSpeedLabel", ""));

    //Listeners
    fpsLabel.setSize(debugGui.getWidth(), fpsLabel.getHeight());
    frameDurationLabel.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
    particlePosition.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
    particleVelocity.setSize(debugGui.getWidth(), frameDurationLabel.getHeight());
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
