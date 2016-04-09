#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxControl.h"
#include "AudioUnitController.h"


class Selection {
public:
    void setAudioUnit(AudioUnitController *au) {
        this->au = au;
    }
    void add(string name) {
        parameters.push_back(name);
    }
    void remove(string name) {
        parameters.erase(std::remove(parameters.begin(), parameters.end(), name), parameters.end());
    }
    void setValue(int idx, float value) {
        if (idx < parameters.size()) {
            float ival = ofLerp(au->getParameter(parameters[idx]).getMin(), au->getParameter(parameters[idx]).getMax(), value);
            au->getParameter(parameters[idx]).set(ival);
        }
    }
    void draw(int x, int y) {
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(x, y);
        for (int i=0; i<parameters.size(); i++) {
            ofSetColor(0);
            ofDrawBitmapString(ofToString(i) + " :: " + parameters[i], 0, (i + 1) * 16);
        }
        ofPopStyle();
        ofPopMatrix();
    }
    
    AudioUnitController *au;
    vector<string> parameters;
};


class Section {
public:
    Section(AudioUnitController *au, string name, vector<AudioUnitParameterInfo> & parameters, ofxControlWidget *gui, Selection *selection) {
        this->au = au;
        this->gui = gui;
        this->selection = selection;
        vector<string> choices;
        for (auto p : parameters) {
            //if (p.flags == 3360686096) { // exponential
            choices.push_back(p.name);
        }
        ofxControlMenu *menu = gui->addMenu(name, choices, this, &Section::eventSelectParameter, true);
        menu->setCollapsed(true);
    }
    void eventSelectParameter(ofxControlMenuEventArgs & e) {
        string name = e.toggle->getName();
        if (e.value) {
            selection->add(name);
        }
        else {
            selection->remove(name);
        }
    }

    AudioUnitController *au;
    ofxControlWidget *gui;
    Selection *selection;
    ofxControlMenu *menu;
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    AudioUnitController au;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    
    ofxControlWidget gui;

    vector<Section*> sections;
    Selection selection;
    
    ofxOscReceiver osc;
};
