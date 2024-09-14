#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(150, 150, 150, 255);
}
//--------------------------------------------------------------
void ofApp::update(){
    //double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame
    particle.update();

    // update lines to draw
    for (int i = 0; i < listOfLines.size(); i++){
		listOfLines[i].second -= ofGetLastFrameTime();
		if (listOfLines[i].second <= 0){
			listOfLines.erase(listOfLines.begin() + i);
		}
	}
   
}

//--------------------------------------------------------------
void ofApp::draw(){

    //To do HERE: Drawing everything
    particle.draw();

    //draw lines
    ofSetColor(ofColor::black);
    ofSetLineWidth(10);
    for (int i = 0; i < listOfLines.size(); i++) {
        ofDrawLine(listOfLines[i].first.first, listOfLines[i].first.second);
    }
    
    //Has to be last so it is drawn above everything else
    drawDebug();
    

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    float radius = particle.getRadius();
    particle.setPosition(maths::vec3(ofGetWidth() - radius, ofGetHeight() -radius, 0));

    particle.setVelocity(maths::vec3(-15, -15, 0));
    particle.setAcceleration(maths::vec3(0, 9.81, 0));

    particle.clearTrail();

    //draw a vector
    float mousex = ofGetMouseX();
    float mousey = ofGetMouseY();
    listOfLines.push_back(std::make_pair(std::make_pair(maths::vec3(ofGetWidth() - radius, ofGetHeight() - radius, 0), maths::vec3(mousex, mousey, 0)), 300));
    ofDrawLine(maths::vec3(ofGetWidth() - radius, ofGetHeight() - radius, 0), maths::vec3(mousex, mousey, 0));
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::drawDebug(){
    ofSetColor(ofColor(255,255,255, 25));
    ofDrawRectangle(5, 5, 400, 70);
    ofSetColor(ofColor::black);
    ofDrawBitmapString("FPS : " + std::to_string(ofGetFrameRate()), 10, 23);
    ofDrawBitmapString("Position : " + particle.getPositionAsString(), 10, 37);
    ofDrawBitmapString("Acceleration : " + particle.getAccelerationAsString(), 10, 51);
    ofDrawBitmapString("Velocity : " + particle.getVelocityAsString(), 10, 65);
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
