#pragma once

#include "ForceRegistry.h"
#include "ofMain.h"
#include "ofEvents.h"
#include "Particle.h"
#include "ofxGui.h"
#include "particlesTypes/bullet.h"
#include "particlesTypes/canonBall.h"
#include "particlesTypes/fireBall.h"



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

	// Display
	ofCamera camera;
	
	// UI STUFF
	bool isDebugEnabled = false;
	ofTrueTypeFont vectorFont;
	ofxPanel controlGui;
	ofxPanel debugGui;
	ofxToggle debugToggle;
	ofxButton resetButton;
	ofxLabel fpsLabel;
	ofxLabel frameDurationLabel;

	void onToggleChanged(bool & value);
	void onResetButtonPressed();

	void drawArrow();
	void drawDebugGui();
	void setupControlGui();
	void setupDebugGui();
};
