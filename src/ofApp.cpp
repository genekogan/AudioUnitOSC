#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //  aalto.setup(&learn, "Aalto", 'aumu', 'Aalt', 'MLbs');
    // kaivo.setup(&learn, "Kaivo", 'aumu', 'Kaiv', 'MLbs');

    au.setup("Aalto", 'aumu', 'Aalt', 'MLbs');
    au.showUI();
    
    au.connectTo(mixer,0);
    mixer.connectTo(output);
    output.start();
    
    selection.setAudioUnit(&au);
    
    gui.setName("Aalto");
    map<string, vector<AudioUnitParameterInfo> >::iterator it = au.getParameterGroups().begin();
    for (; it != au.getParameterGroups().end(); ++it) {
        Section *section = new Section(&au, it->first, au.getParameterGroups()[it->first], &gui, &selection);
    }
    
    osc.setup(12000);
}

//--------------------------------------------------------------
void ofApp::update(){
    while (osc.hasWaitingMessages()) {
        ofxOscMessage msg;
        osc.getNextMessage(msg);
        if (msg.getAddress() == "/wek/outputs") {
            for (int i=0; i<msg.getNumArgs(); i++) {
                selection.setValue(i, msg.getArgAsFloat(i));
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255);
    ofPushStyle();
    ofSetColor(0);
    ofDrawBitmapString("Parameters", 300, 90);
    ofDrawLine(300, 94, 400, 94);
    ofPopStyle();
    selection.draw(300, 120);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    au.getSynth().midiNoteOn(70, 127);
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
