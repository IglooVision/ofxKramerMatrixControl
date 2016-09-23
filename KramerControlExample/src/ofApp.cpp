#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	ofLogToFile("logFile.txt", true);

	kramerControl.loadXmlSettings("KramerMatrixSettings.xml");

	kramerControl.setupKramerConnection();

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofClear(0);
	ofDrawBitmapString("Press q to send command 0", 100, 100);
	ofDrawBitmapString("Press w to send command 1", 100, 150);
	ofDrawBitmapString("Press e to switch to preset 1", 100, 200);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'q')
	{
		kramerControl.sendCommand(0);
	}
	if (key == 'w')
	{
		kramerControl.sendCommand(1);
	}
	if (key == 'e')
	{
		kramerControl.sendSwitchPresetCommand(1);
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
