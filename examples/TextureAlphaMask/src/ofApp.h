#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp {
    void setupBackgroundGradientMesh();
    void setupMaskedGradientMesh();
    void setupFBOs();
    void generateMask();
    void drawMask();
    void setMeshToShape();
    void setMeshToOutline();
    ofVboMesh m_bg_gradient, m_masked_gradient;
    ofMesh m_mask_mesh;
    ofFbo m_mask_fbo, m_gradient_fbo;
    ofVec2f m_pos_1, m_pos_2, m_pos_3;
    int m_num_samples;
    bool m_smoothing_enabled, m_outline_enabled;
public:
    void setup();
//    void update();
    void draw();

    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
//    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
};
