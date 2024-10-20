#pragma once

#include <unordered_set>

#include "CollisionDetector.h"
#include "CollisionResolver.h"
#include "ForceRegistry.h"
#include "ofMain.h"
#include "ofEvents.h"
#include "Particle.h"
#include "ofxGui.h"
#include "forces/TwoParticleSpringForceGenerator.h"

#include "particlesTypes/bullet.h"
#include "particlesTypes/canonBall.h"
#include "particlesTypes/fireBall.h"

#include "forces/Ressort.h"
#include "forces/Bungee.h"



class ofApp : public ofBaseApp
{
public:
    void setup();
    void update();
    void draw();

	~ofApp();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
	// Particles
	std::vector<Particle*> particles;
	std::vector<ForceGenerator*> forces;
	ForceRegistry registry;
	CollisionDetector collisionDetector;
	CollisionResolver collisionResolver;

	// Blob
	std::vector<Particle*> blob;
	std::vector<TwoParticleSpringForceGenerator*> blobSprings;
	float forceToSeparateParticles = 1000.0f;

	// Used for grabbing particles
	Particle* selectedParticle = nullptr;
	vec3 selectionPlaneNormal = vec3(0, 1, 0);
	vec3 selectionPlanePoint = vec3(0, 0, 0);

	// Display
	ofEasyCam camera;
	
	// UI STUFF
	bool isDebugEnabled = false;
	ofTrueTypeFont vectorFont;
	ofxPanel controlGui;
	ofxPanel debugGui;
	ofxToggle debugToggle;
	ofxButton resetButton;
	ofxLabel fpsLabel;
	ofxLabel frameDurationLabel;
	ofxLabel blobNumberLabel;

	ofxLabel particlePosition;
	ofxLabel particleVelocity;
	ofxLabel speedLabel;

	void onToggleChanged(bool & value);
	void onResetButtonPressed();

	void drawDebugGui();
	void setupControlGui();
	void setupDebugGui();
};
