#include "ofApp.h"


void ofApp::setup(){
    ofLog() << glGetString(GL_VERSION);
    
    ofSetFrameRate(60);
    ofSetBackgroundColor(33);
    ofSetBackgroundAuto(true);
    
    float w = ofGetWidth() * 0.25f;
    float h = ofGetHeight() * 0.25f;
    
    m_mesh.setMode(OF_PRIMITIVE_POINTS);
    m_mesh.addVertex(ofVec3f(0.f, 0.f, 0.f));
    m_mesh.addVertex(ofVec3f(-w, -h, 0.f));
    m_mesh.addVertex(ofVec3f(w, -h, 0.f));
    m_mesh.addVertex(ofVec3f(w, h, 0.f));
    m_mesh.addVertex(ofVec3f(-w, h, 0.f));
    
    m_shader.setGeometryInputType(GL_POINTS);
    m_shader.setGeometryOutputType(GL_TRIANGLES);
    m_shader.setGeometryOutputCount(3);
    m_shader.load("shaders/pass_through.vert", "shaders/prog_geometry.frag", "shaders/prog_geometry.geom");
    
    m_fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA, 8);
    m_fbo.begin();
    ofClear(0);
    m_fbo.end();
    
    m_panel.setup("Geometry Shader");
    m_panel.setPosition(300, 10);
    m_panel.add(m_param_enable_shader.set("enable shader", true));
    m_panel.add(m_param_segments.set("segments", 30, 3, 50));
    m_panel.add(m_param_radius.set("radius", 150, 50, 300));
    m_panel.add(m_param_amplitude.set("amplitude", 50, 0, 150));
    m_panel.add(m_param_speed.set("speed", 2.f, 1.f, 10.f));
    m_panel.add(m_param_clear_fbo.set("clear fbo", true));
    
    m_show_panel = false;
}


void ofApp::update(){
    
    m_info = "FPS: " + to_string((int) ofGetFrameRate());
    m_info += "\nUse mouse to interact with camera.";
    m_info += "\nPress 'g' to ";
    m_info += m_show_panel ? "hide" : "show";
    m_info += " gui panel.";
    
    m_fbo.begin();
    
    if (m_param_clear_fbo) {
        ofClear(0);
    }
    
    ofEnableDepthTest();
    
    m_cam.begin();
    
    if (m_param_enable_shader) {
        m_shader.begin();
        m_shader.setUniform1i("segments", m_param_segments);
        m_shader.setUniform1i("radius", m_param_radius);
        m_shader.setUniform1i("amplitude", m_param_amplitude);
        m_shader.setUniform1f("speed", ofGetElapsedTimef() / m_param_speed);
    }
    
    m_mesh.draw();
    
    if (m_param_enable_shader) {
        m_shader.end();
    }
    
    m_cam.end();
    
    ofDisableDepthTest();
    
    m_fbo.end();
}


void ofApp::draw() {
    ofDrawBitmapString(m_info, 10, 21);
    
    m_fbo.draw(0, 0);
    
    if (m_show_panel) {
        m_panel.draw();
    }
}


void ofApp::keyPressed(int key){
    if (key == 'g') {
        m_show_panel = !m_show_panel;
    }
}

