#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "VectorFieldInputFactory.h"
#include "VectorFieldInputProvider.h"
#include "VectorField.h"
#include "ParticleSystem.h"


class ofApp : public ofBaseApp {
    void updateGuiPosition();
    void updateGui();
    void updateInputProvider(const VectorFieldInputType type);
    ofVec2f mCenteredPos;
    bool mShowGui;
    ofxPanel mGui;
    VectorFieldInputType mDefaultType = VectorFieldInputType::NOISE;
    VectorFieldInputFactory mInputFactory;
    VectorFieldInputProvider* mInputProvider;
    VectorField mVectorField;
    ParticleSystem mParticleSystem;
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
};
