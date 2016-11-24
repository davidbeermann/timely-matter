#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "opencv2/opencv.hpp"


class ofApp : public ofBaseApp {
    
    ofImage m_image;
    ofxCvColorImage m_cv_image;
    cv::Subdiv2D m_subdivision;
    vector<cv::Vec6f> m_triangles;
    ofVec2f m_image_pos;
    vector<cv::Point2f> m_points;
    cv::Rect m_boundary;
    ofMesh m_delaunay_mesh;
    ofMesh m_voronoi_mesh;
    
    ofColor averageColor(vector<ofColor>& colors);
    ofFloatColor averageFloatColor(vector<ofColor>& colors);

public:
    void setup();
    void update();
    void draw();
//    void keyPressed(int key);
//    void keyReleased(int key);
//    void mouseMoved(int x, int y );
//    void mouseDragged(int x, int y, int button);
//    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
//    void mouseEntered(int x, int y);
//    void mouseExited(int x, int y);
    void windowResized(int w, int h);
//    void dragEvent(ofDragInfo dragInfo);
//    void gotMessage(ofMessage msg);
		
};
