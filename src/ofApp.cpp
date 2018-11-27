#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFullscreen(true);

    SceneManager::setup("TitleScene", new TitleScene());
}

//--------------------------------------------------------------
void ofApp::update(){
    SceneManager::update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    SceneManager::draw();
}

void ofApp::exit()
{
    SceneManager::exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    SceneManager::keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    SceneManager::keyReleased(key);
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    SceneManager::mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    SceneManager::mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    SceneManager::mouseReleased(x, y, button);
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
