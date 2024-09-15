#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150, 150, 150, 255);
    initialVelocity.first = maths::vec3(ofGetWidth(), ofGetHeight(), 0);

    //Font related shenaningans for displaying vectors
    string path = ofFilePath::getEnclosingDirectory(ofFilePath::getCurrentWorkingDirectory())+
        "src/externalressources/Fonts/LatinModern.otf";
    ofTrueTypeFontSettings settings(path, 32);
    ofUnicode::range vectorArrow(0x20D7, 0x20D7);
    ofUnicode::range underZero(0x2080, 0x2089);
    settings.addRange(vectorArrow);
    settings.addRange(underZero);
    settings.addRanges(ofAlphabet::Latin);
    vectorFont.load(settings);
}
//--------------------------------------------------------------
void ofApp::update(){
    //double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame
    particle.update();
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    //To do HERE: Drawing everything
    particle.draw();

    //draw lines
    drawArrow();
    
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
    float mousex = ofGetMouseX();
    float mousey = ofGetMouseY();
    
    particle.setPosition(maths::vec3(ofGetWidth() - radius, ofGetHeight() -radius, 0));
    particle.setVelocity(maths::vec3(-5, -5, 0));
    particle.setAcceleration(maths::vec3(0, 9.81, 0));

    particle.clearTrail();

    initialVelocity.second = maths::vec3(mousex, mousey,0);
    isLineDrawable = true;
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
    initialVelocity.first = maths::vec3(ofGetWidth(), ofGetHeight(), 0);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::drawDebug(){
    ofSetColor(ofColor(255,255,255, 25));
    ofDrawRectangle(5, 5, 400, 90);
    ofSetColor(ofColor::black);
    ofDrawBitmapString("FPS : " + std::to_string(ofGetFrameRate()), 10, 23);
    ofDrawBitmapString("Frame duration : " + std::to_string(ofGetLastFrameTime()*1000)+ " ms", 10, 37) ;
    ofDrawBitmapString("Position : " + particle.getPositionAsString(), 10, 51);
    ofDrawBitmapString("Acceleration : " + particle.getAccelerationAsString(), 10, 65);
    ofDrawBitmapString("Velocity : " + particle.getVelocityAsString(), 10, 79);
}

void ofApp::drawArrow(){
    if(isLineDrawable){
        ofSetColor(ofColor::blueViolet);
        ofSetLineWidth(5);

        float textX = initialVelocity.second.x() -10 ;
        float textY = initialVelocity.second.y()- 15;
        std::string vectorIcon = "v";
        ofUTF8Append(vectorIcon,0x20D7);
        //ofUTF8Append(vectorIcon,0x2080);
        
        ofDrawArrow(initialVelocity.first, initialVelocity.second, 10.0);
        ofSetColor(ofColor::black);

        vectorFont.drawString(vectorIcon, textX, textY);
    }
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
