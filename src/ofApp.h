#pragma once

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

    //a changer
    Particle particle = Particle(maths::vec3(-100, -100, 0), maths::vec3(), maths::vec3()
                                 , 0.0, ofColor::blue, 30, true, 10, 0);
    Bullet bullet = Bullet(maths::vec3(-100, 100, 0));

	private:	
		bool isLineDrawable = false;
		bool isDebugEnabled = false;
		std::pair<maths::vec3,maths::vec3> initialVelocity;
		ofTrueTypeFont vectorFont;
		ofxPanel controlGui;
		ofxPanel debugGui;
		ofxToggle debugToggle;
		ofxButton nextProjectileButton;
		ofxButton launchButton;
		ofxButton resetButton;
		ofxLabel nextProjectileLabel;
		ofxLabel fpsLabel;
		ofxLabel frameDurationLabel;
		ofxLabel positionLabel;
		ofxLabel accelerationLabel;
		ofxLabel velocityLabel;

		void onToggleChanged(bool & value);
		void onNextProjectileButtonPressed();
		void onLaunchButtonPressed();
		void onResetButtonPressed();
	
		void drawArrow();
		void drawDebugGui();
		void setupControlGui();
		void setupDebugGui();
};
