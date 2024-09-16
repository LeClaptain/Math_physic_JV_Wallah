#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofGLWindowSettings settings;
	//settings.windowMode = OF_FULLSCREEN;
	//settings.setSize(1280, 720);
	auto window = ofCreateWindow(settings);

	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
