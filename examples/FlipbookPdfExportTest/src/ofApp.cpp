#include "ofApp.h"

#define NUM_CIRCLES 20
#define CIRCLE_MIN_RADIUS 25
#define CIRCLE_MAX_RADIUS 75
#define CAPTURE_RATE 6
#define CAPTURE_MAX_COUNT 10
#define SAVE_FILE_MODE ofCairoRenderer::PDF


// saves a PDF or SVG file with transparent background
// implementation derived from the following forum posts:
// https://forum.openframeworks.cc/t/save-screen-as-pdf-without-the-background/20334
// https://forum.openframeworks.cc/t/saving-screen-as-pdf-without-background/10377/
void ofApp::saveFile() {
    
    // create renderer
    ofCairoRenderer renderer;
    
    // define special viewport size for renderer
//    ofRectangle viewport;
//    viewport.set(0, 0, 1000, 2000); // renderer dimensions
//    ofViewport(viewport);
    
    // incrementcapture count
    m_capture_count++;
    
    // SET FILE NAME
    // -------------
    // padding the file name count with zeros
    // ensures that the sequence is preserved during placement in InDesign
    string num = "";
    int max = to_string(CAPTURE_MAX_COUNT).length();
    int l = to_string(m_capture_count).length();
    if (l < max) {
        for (int i = 0; i < max - l; ++i) {
            num += "0";
        }
    }
    num += to_string(m_capture_count);
    string file_name = "frame-" + num;
    
    // setup renderer
    if (SAVE_FILE_MODE == ofCairoRenderer::PDF) {
        renderer.setup(m_files_folder+"/"+file_name+".pdf", ofCairoRenderer::PDF);
    } else if(SAVE_FILE_MODE == ofCairoRenderer::SVG) {
        renderer.setup(m_files_folder+"/"+file_name+".svg", ofCairoRenderer::SVG);
    } else {
        ofLog() << "Unknown file mode.";
        return;
    }
    
    renderer.viewport(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    renderer.setBlendMode(OF_BLENDMODE_ALPHA);
    renderer.setBackgroundColor(ofColor(0,0,0,0));
    renderer.setFillMode(OF_FILLED);
    
    // draw contents
    vector<ofVec3f>::iterator c;
    for (c = m_circles.begin(); c != m_circles.end(); ++c) {
        renderer.pushMatrix();
        renderer.translate(c->x, c->y);
        renderer.pushStyle();
        renderer.setColor(255);
        renderer.drawEllipse(0.f, 0.f, 0.f, c->z, c->z);
        renderer.popStyle();
        renderer.popMatrix();
    }
    
    // close renderer
    renderer.close();
    
    // reset to screen viewpoer size
//    ofViewport(ofRectangle(0,0,ofGetWidth(),ofGetHeight()));
    
}


void ofApp::setup(){
    
    ofSetBackgroundAuto(true);
    ofSetBackgroundColor(255, 255, 255, 0);
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    
    // create unique folder name for each time the application runs
    m_files_folder = to_string(ofGetYear());
    m_files_folder += to_string(ofGetMonth());
    m_files_folder += to_string(ofGetDay());
    m_files_folder += "-";
    m_files_folder += to_string(ofGetHours());
    m_files_folder += to_string(ofGetMinutes());
    m_files_folder += to_string(ofGetSeconds());
    
    for (unsigned int i = 0; i < NUM_CIRCLES; ++i) {
        m_circles.push_back(ofVec3f(
            ofRandom(0, ofGetWidth()),
            ofRandom(0, ofGetHeight()),
            ofRandom(CIRCLE_MIN_RADIUS, CIRCLE_MAX_RADIUS)
        ));
    }
    
    m_frame_increment = 60 / CAPTURE_RATE;
    m_frame_count = 0;
    m_save_file = false;
    
    m_capture_activated = false;
    m_capture_count = 0;
    
}


void ofApp::update(){
    
    if (m_capture_count >= CAPTURE_MAX_COUNT) {
        m_capture_activated = false;
        m_capture_count = 0;
        ofLog() << "All frames captured.";
    }
    
    if (m_save_file) {
        m_frame_count = 0;
        m_save_file = false;
    }
    
    vector<ofVec3f>::iterator c;
    for (c = m_circles.begin(); c != m_circles.end(); ++c) {
        c->x += ofRandom(-3, 3);
        c->y += ofRandom(-3, 3);
    }
    
    if (m_capture_activated) {
        m_save_file = (++m_frame_count >= m_frame_increment);
    }
    
    if (m_save_file) {
        saveFile();
    }
    
}


void ofApp::draw() {
    
    if (m_save_file) {
        // draw flashing background for each frame captured
        ofPushStyle();
        ofSetColor(255, 127, 127);
        ofDrawRectangle(0.f, 0.f, ofGetWidth(), ofGetHeight());
        ofPopStyle();
    }
    
    vector<ofVec3f>::iterator c;
    for (c = m_circles.begin(); c != m_circles.end(); ++c) {
        ofPushMatrix();
        ofTranslate(c->x, c->y);
        ofPushStyle();
        if (m_save_file) {
            ofSetColor(255);
        } else {
            ofSetColor(127);
        }
        ofDrawEllipse(0, 0, c->z, c->z);
        ofPopStyle();
        ofPopMatrix();
    }
    
}


void ofApp::keyPressed(int key) {
    
    if (key == 'a') {
        m_capture_activated = !m_capture_activated;
    }
    
}

