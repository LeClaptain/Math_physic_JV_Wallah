#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    ofBackground(150, 150, 150, 255);
    initialVelocity.first = maths::vec3(ofGetWidth(), ofGetHeight(), 0);

    //GUI
    setupControlGui();
    setupDebugGui();
    debugGui.setWidthElements(400);

    //Font related shenaningans for displaying vectors
    string path = ofFilePath::getEnclosingDirectory(ofFilePath::getCurrentWorkingDirectory())+
        "src/externalressources/Fonts/LatinModern.otf"; // TODO : find a font that supports the characters mentioned bellow
    ofTrueTypeFontSettings settings(path, 32);
    ofUnicode::range vectorArrow(0x20D7, 0x20D7); //adds the unicode character for a vector
    ofUnicode::range underZero(0x2080, 0x2089); //adds the unicode charactor for all numbers as indexes
    settings.addRange(vectorArrow);
    settings.addRange(underZero);
    settings.addRanges(ofAlphabet::Latin);
    vectorFont.load(settings);
}
//--------------------------------------------------------------
void ofApp::update(){
    //double lastFrame = ofGetLastFrameTime(); //gets Δt since last frame
    particle.update();
    bullet.update();
   
}

//--------------------------------------------------------------
void ofApp::draw(){

    //To do HERE: Drawing everything
    particle.draw();
    bullet.draw();

    //draw lines
    drawArrow();
    
    controlGui.draw();

    if(isDebugEnabled)
    {
        drawDebugGui();
    }
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
    particle.setVelocity(maths::vec3(-500, -500, 0));
    particle.setAcceleration(maths::vec3(0, 9.81*50, 0));

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
    controlGui.setPosition(10,ofGetHeight()-100);
    debugGui.setPosition(10,10);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::drawDebugGui(){
    debugGui.draw();
    fpsLabel.setName("FPS: " + std::to_string(ofGetFrameRate()));
    frameDurationLabel.setName("Frame Duration: " + std::to_string(ofGetFrameRate()));
    positionLabel.setName("Position: " + particle.getPositionAsString());
    velocityLabel.setName("Velocity: " + particle.getVelocityAsString());
    accelerationLabel.setName("Acceleration: " + particle.getAccelerationAsString());
    /*
    ofSetColor(ofColor(255,255,255, 25));
    ofDrawRectangle(5, 5, 400, 90);
    ofSetColor(ofColor::black);
    ofDrawBitmapString("FPS : " + std::to_string(ofGetFrameRate()), 10, 23);
    ofDrawBitmapString("Frame duration : " + std::to_string(ofGetLastFrameTime()*1000)+ " ms", 10, 37) ;
    ofDrawBitmapString("Position : " + particle.getPositionAsString(), 10, 51);
    ofDrawBitmapString("Acceleration : " + particle.getAccelerationAsString(), 10, 65);
    ofDrawBitmapString("Velocity : " + particle.getVelocityAsString(), 10, 79);*/
}

void ofApp::setupControlGui(){
    controlGui.setup("",  ofxPanelDefaultFilename, 10,  ofGetHeight()-100);
    controlGui.add(launchButton.setup("Launch projectile"));
    controlGui.add(nextProjectileButton.setup("Next projectile"));
    controlGui.add(resetButton.setup("Reset the scene"));
    controlGui.add(debugToggle.setup("Debug Toggle", false));

    launchButton.addListener(this, &ofApp::onLaunchButtonPressed);
    nextProjectileButton.addListener(this, &ofApp::onNextProjectileButtonPressed);
    resetButton.addListener(this, &ofApp::onResetButtonPressed);
    debugToggle.addListener(this, &ofApp::onToggleChanged);

}

void ofApp::setupDebugGui()
{
    debugGui.setup();
    debugGui.add(fpsLabel.setup("fpsLabel", ""));
    debugGui.add(frameDurationLabel.setup("frameDurationLabel", ""));
    debugGui.add(positionLabel.setup("positionLabel", ""));
    debugGui.add(velocityLabel.setup("velocityLabel", ""));
    debugGui.add(accelerationLabel.setup("accelerationLabel", ""));
}


void ofApp::onToggleChanged(bool& value)
{
    isDebugEnabled = value;
}

void ofApp::onNextProjectileButtonPressed()
{
    std :: cout << "Next projectile" << std :: endl;
}

void ofApp::onLaunchButtonPressed()
{
    std :: cout << "Launch projectile" << std :: endl;
}

void ofApp::onResetButtonPressed()
{
    std :: cout << "Reset projectile" << std :: endl;
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
