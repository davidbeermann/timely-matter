#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    void saveFile();
    string m_files_folder;
    unsigned int m_frame_count;
    unsigned int m_frame_increment;
    bool m_save_file;
    bool m_capture_activated;
    unsigned int m_capture_count;
    vector<ofVec3f> m_circles;
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
//    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
};
