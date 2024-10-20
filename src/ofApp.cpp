#include "ofApp.h"

#include "forces/GravityForceGenerator.h"

#include "forces/TwoParticleSpringForceGenerator.h"
#include "forces/FrictionForceGenerator.h"
#include "forces/Ressort.h"
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

    //basics - GREEN, RED, BLUE
    Particle* basic1 = new Particle(vec3(-19, 100, 0), 2, ofColor::green);
    particles.push_back(basic1);
    collisionDetector.addParticle(basic1);
    Particle* basic2 = new Particle(vec3(20, 80, 0), 2, ofColor::red);
    particles.push_back(basic2);
    collisionDetector.addParticle(basic2);
    Particle* basic3 = new Particle(vec3(0, 20, 0), 1, ofColor::blue);
    particles.push_back(basic3);
    collisionDetector.addParticle(basic3);

    //Springs - BLUEVIOLET
    Particle* spring1 = new Particle(vec3(0, 80, 0), 2, ofColor::blueViolet);
    particles.push_back(spring1);
    collisionDetector.addParticle(spring1);
    Ressort* spring = new Ressort(2, 50, vec3(0, 150, 0));
    registry.add({spring1}, spring);
    forces.push_back(spring);

    //Bungee - PINK AND BLACK
    Particle* bungee1 = new Particle(vec3(100, 100, 0), 3, ofColor::pink);
    particles.push_back(bungee1);
    collisionDetector.addParticle(bungee1);
    Particle* bungee2 = new Particle(vec3(100, 150, 0), 3, ofColor::black);
    particles.push_back(bungee2);
    collisionDetector.addParticle(bungee2);
    Bungee* bungee = new Bungee(3, 50, bungee1, bungee2);
    registry.add({bungee1, bungee2}, bungee);
    forces.push_back(bungee);

    //Rod - PURPLE
    Particle* rod1 = new Particle(vec3(-50, 100, 0), 3, ofColor::purple);
    particles.push_back(rod1);
    collisionDetector.addParticle(rod1);
    Particle* rod2 = new Particle(vec3(-100, 100, 0), 3, ofColor::purple);
    particles.push_back(rod2);
    collisionDetector.addParticle(rod2);
    collisionDetector.addRelation(RelationType::ROD, rod1, rod2, 50);

    // Cable - FORESTGREEN
    Particle* cable1 = new Particle(vec3(150, 100, 0), 3, ofColor::forestGreen);
    particles.push_back(cable1);
    collisionDetector.addParticle(cable1);
    Particle* cable2 = new Particle(vec3(200, 100, 0), 3, ofColor::forestGreen);
    particles.push_back(cable2);
    collisionDetector.addParticle(cable2);
    collisionDetector.addRelation(RelationType::CABLE, cable1, cable2, 50);

    //Double Spring - ORANGERED AND YELLOW
    Particle* dSpring1 = new Particle(vec3(-150, 100, 0), 3, ofColor::orangeRed);
    particles.push_back(dSpring1);
    collisionDetector.addParticle(dSpring1);
    Particle* dSpring2 = new Particle(vec3(-200, 100, 0), 3, ofColor::yellow);
    particles.push_back(dSpring2);
    collisionDetector.addParticle(dSpring2);

    TwoParticleSpringForceGenerator* twoSideSpring = new TwoParticleSpringForceGenerator(dSpring1, dSpring2, 3, 50);
    registry.add({dSpring1, dSpring2}, twoSideSpring);
    forces.push_back(twoSideSpring);

    GravityForceGenerator* gravity = new GravityForceGenerator();
    forces.push_back(gravity);
    FrictionForceGenerator* friction = new FrictionForceGenerator(0.001, 0);
    forces.push_back(friction);

    registry.add({
                     basic1,
                     basic2,
                     basic3,
                     spring1,
                     bungee1,
                     bungee2,
                     rod1,
                     rod2,
                     cable1,
                     cable2,
                     dSpring1,
                     dSpring2
                 }, gravity);
    registry.add({
                     basic1,
                     basic2,
                     basic3,
                     spring1,
                     bungee1,
                     bungee2,
                     rod1,
                     rod2,
                     cable1,
                     cable2,
                     dSpring1,
                     dSpring2
                 }, friction);

    collisionResolver.setElasticity(0.5f);

    camera.setPosition(vec3(0, 0, 500));

    camera.lookAt(vec3(0));
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

        vec3 force = (intersection - selectedParticle->getPosition()) * 10;

        selectedParticle->addForce(force);
    }

    registry.updateForces(lastFrame);

    auto collisions = collisionDetector.solve(lastFrame);
    collisionResolver.resolveCollisions(collisions);

    // euler integration
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

    collisionDetector.debugDrawRelations();
    for (const auto& force : forces)
    {
        force->debugDraw();
    }

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
