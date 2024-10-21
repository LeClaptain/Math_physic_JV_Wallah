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
    collisionDetector.addRelation(ROD, rod1, rod2, 50);

    // Cable - FORESTGREEN
    Particle* cable1 = new Particle(vec3(150, 100, 0), 3, ofColor::forestGreen);
    particles.push_back(cable1);
    collisionDetector.addParticle(cable1);
    Particle* cable2 = new Particle(vec3(200, 100, 0), 3, ofColor::forestGreen);
    particles.push_back(cable2);
    collisionDetector.addParticle(cable2);
    collisionDetector.addRelation(CABLE, cable1, cable2, 50);

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
    FrictionForceGenerator* friction = new FrictionForceGenerator(0.1, 0);
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


    //Blob - GOLD
    vector<vec3> positions;
    positions.push_back(vec3(300, 100, 50));
    positions.push_back(vec3(300 - 50, 100, 50));
    positions.push_back(vec3(300 - 50, 100 - 50, 50));
    positions.push_back(vec3(300, 100 - 50, 50));
    positions.push_back(vec3(300, 100, 0));
    positions.push_back(vec3(300 - 50, 100, 0));
    positions.push_back(vec3(300 - 50, 100 - 50, 0));
    positions.push_back(vec3(300, 100 - 50, 0));
    for (int i = 0; i < positions.size(); i++)
    {
        Particle* p;
        if (i == 0)
        {
            p = new Particle(positions[i], 2, ofColor::coral);
        }
        else
        {
            p = new Particle(positions[i], 2, ofColor::gold);
        }
        blob.push_back(p);
        particles.push_back(p);
        collisionDetector.addParticle(p);
        registry.add(p, gravity);
        registry.add(p, friction);
    }

    // ajout des forces dans le blob
    vector<pair<int, int>> links;
    links.push_back({0, 1});
    links.push_back({1, 2});
    links.push_back({2, 3});
    links.push_back({3, 0});
    links.push_back({4, 5});
    links.push_back({5, 6});
    links.push_back({6, 7});
    links.push_back({7, 4});
    links.push_back({0, 4});
    links.push_back({1, 5});
    links.push_back({2, 6});
    links.push_back({3, 7});

    for (pair<int, int> pr : links)
    {
        int i = pr.first;
        int j = pr.second;
        //float length = (positions[i]-positions[j]).magnitude();
        TwoParticleSpringForceGenerator* blobSpring = new TwoParticleSpringForceGenerator(blob[i], blob[j], 10, 60);
        blobSprings.push_back(blobSpring);
        registry.add({blob[i], blob[j]}, blobSpring);
        forces.push_back(blobSpring);
        collisionDetector.addRelation(RelationType::CABLE, blob[i], blob[j], 100);
    }

    collisionResolver.setElasticity(0.5f);

    camera.setPosition(vec3(0, 0, 500));

    camera.setFarClip(10000.0f);

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

    

    // Check if we need to remove links from the blob
    for (int i = 0; i < blobSprings.size(); i++)
    {
        if (blobSprings[i]->getParticle1()->getForces().magnitude() > forceToSeparateParticles || blobSprings[i]->
            getParticle2()->
            getForces().magnitude() > forceToSeparateParticles)
        {
            registry.remove({blobSprings[i]->getParticle1(), blobSprings[i]->getParticle2()}, blobSprings[i]);
            collisionDetector.removeRelation(blobSprings[i]->getParticle1(), blobSprings[i]->getParticle2());
            forces.erase(std::remove(forces.begin(), forces.end(), blobSprings[i]), forces.end());
            delete blobSprings[i];
            blobSprings.erase(blobSprings.begin() + i);

            for (auto it = blob.begin(); it != blob.end(); ) {
                if (*it == selectedParticle) {
                    it = blob.erase(it);
                } else {
                    ++it;
                }
            }
            i--;
        }
    }

    // find and solve collisions
    auto collisions = collisionDetector.solve(lastFrame);
    collisionResolver.resolveCollisions(collisions);

    // Update generators
    registry.updateForces(lastFrame);

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
    // drawArrow();

    // Draw scene
    camera.begin();
    ofEnableDepthTest();
    for (const auto& particle : particles)
    {
        particle->draw();
    }
    ofDrawGrid(10.f, 10, false, false, true, false);
    ofDisableDepthTest();

    // debug
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
