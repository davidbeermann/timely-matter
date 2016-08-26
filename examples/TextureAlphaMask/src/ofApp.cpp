#include "ofApp.h"

#define GRADIENT_OFFSET 30
#define MESH_WIDTH 300
#define MESH_HEIGHT 300


void ofApp::setup() {
    ofSetFrameRate(60);
    
    // https://www.opengl.org/wiki/Multisampling
    m_num_samples = 4;
    m_smoothing_enabled = false;
    m_outline_enabled = false;
    
    m_pos_1.set(50.f, 50.f);
    m_pos_2.set(400.f, 50.f);
    m_pos_3.set(750.f, 50.f);
    
    setupBackgroundGradientMesh();
    setupMaskedGradientMesh();
    
    setupFBOs();
    
    generateMask();
    drawMask();
}


void ofApp::draw() {
    string info = "";
    info += "Number of Samples: " + to_string(m_num_samples);
    info += " - Smoothing Enabled: " + to_string(m_smoothing_enabled);
    info += " - Outline Enabled: " + to_string(m_outline_enabled);
    
    ofPushStyle();
    ofSetColor(33);
    ofDrawBitmapString(info, 10, 20);
    ofPopStyle();
    
    ofPushMatrix();
    ofTranslate(GRADIENT_OFFSET, GRADIENT_OFFSET);
    m_bg_gradient.draw();
    ofPopMatrix();
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(m_pos_1);
    ofSetColor(255);
    ofDrawBitmapString("PLAIN MESH", 0, -5.f);
    ofSetColor(255);
    m_mask_mesh.draw();
    ofPopMatrix();
    ofPopStyle();
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(m_pos_2);
    ofSetColor(255);
    ofDrawBitmapString("MESH DRAWN TO FBO", 0.f, -5.f);
    ofSetColor(255);
    m_mask_fbo.draw(0, 0);
    ofPopMatrix();
    ofPopStyle();
    
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(m_pos_3);
    ofSetColor(255);
    ofDrawBitmapString("FBO AS ALPHA MASK", 0.f, -5.f);
    m_gradient_fbo.draw(0, 0);
    ofPopMatrix();
    ofPopStyle();
}


void ofApp::keyPressed(int key) {
    switch (key) {
        case ' ':
            generateMask();
            drawMask();
            break;
        
        case 'o':
            m_outline_enabled = !m_outline_enabled;
            break;
            
        case 's':
            m_smoothing_enabled = !m_smoothing_enabled;
            break;
        
        case OF_KEY_UP:
            if (m_num_samples == 0) {
                m_num_samples = 2;
            } else {
                m_num_samples *= 2;
            }
            
            if (m_num_samples > ofFbo::maxSamples()) {
                ofLog() << "your gfx card is limited to maximum number of MSAA samples: " << ofFbo::maxSamples();
                m_num_samples = ofFbo::maxSamples();
            } else {
                
            }
            
            setupFBOs();
            drawMask();
            break;
            
        case OF_KEY_DOWN:
            if (m_num_samples == 2) {
                m_num_samples = 0;
            } else {
                m_num_samples /= 2;
            }
            
            setupFBOs();
            drawMask();
            break;
            
        default:
            break;
    }
}


void ofApp::setupFBOs() {
    if (m_mask_fbo.isAllocated()) {
        m_mask_fbo.clear();
    }
    
    m_mask_fbo.allocate(MESH_WIDTH, MESH_HEIGHT, GL_RGBA, m_num_samples);
    
    m_mask_fbo.begin();
    ofClear(0);
    m_mask_fbo.end();
    
    if (m_gradient_fbo.isAllocated()) {
        m_gradient_fbo.clear();
    }
    
    m_gradient_fbo.allocate(MESH_WIDTH, MESH_HEIGHT, GL_RGBA, m_num_samples);
    
    m_gradient_fbo.begin();
    ofSetColor(255);
    m_masked_gradient.draw();
    m_gradient_fbo.end();
    
    m_gradient_fbo.getTexture().setAlphaMask(m_mask_fbo.getTexture());
}


void ofApp::drawMask() {
    m_mask_fbo.begin();
    ofClear(0);
    if (m_smoothing_enabled) ofEnableSmoothing();
    ofSetColor(255);
    if (m_outline_enabled) {
        setMeshToOutline();
        m_mask_mesh.draw();
        setMeshToShape();
    }
    m_mask_mesh.draw();
    if (m_smoothing_enabled) ofDisableSmoothing();
    m_mask_fbo.end();
}


void ofApp::setMeshToShape() {
    m_mask_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    m_mask_mesh.enableIndices();
    m_mask_mesh.addIndices({
        0, 1, 3,
        1, 2, 3
    });
}


void ofApp::setMeshToOutline() {
    m_mask_mesh.setMode(OF_PRIMITIVE_LINE_LOOP);
    
    m_mask_mesh.disableIndices();
    m_mask_mesh.clearIndices();
}


void ofApp::generateMask() {
    m_mask_mesh.clear();
    
    m_mask_mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    
    m_mask_mesh.addVertex(ofVec3f(ofRandom(5.f, 50.f), ofRandom(5.f, 50.f), 0.f));
    m_mask_mesh.addVertex(ofVec3f(MESH_WIDTH - ofRandom(5.f, 50.f), ofRandom(5.f, 50.f), 0.f));
    m_mask_mesh.addVertex(ofVec3f(MESH_WIDTH - ofRandom(5.f, 50.f), MESH_HEIGHT - ofRandom(5.f, 50.f), 0.f));
    m_mask_mesh.addVertex(ofVec3f(ofRandom(5.f, 50.f), MESH_HEIGHT - ofRandom(5.f, 50.f), 0.f));
    
    m_mask_mesh.enableIndices();
    m_mask_mesh.addIndices({
        0, 1, 3,
        1, 2, 3
    });
}


void ofApp::setupMaskedGradientMesh() {
    m_masked_gradient.setMode(OF_PRIMITIVE_TRIANGLES);
    
    m_masked_gradient.addVertex(ofVec3f(0.f, 0.f, 0.f));
    m_masked_gradient.addVertex(ofVec3f(MESH_WIDTH, 0.f, 0.f));
    m_masked_gradient.addVertex(ofVec3f(MESH_WIDTH, MESH_HEIGHT, 0.f));
    m_masked_gradient.addVertex(ofVec3f(0.f, MESH_HEIGHT, 0.f));
    
    m_masked_gradient.enableColors();
    m_masked_gradient.addColors({
        ofColor(255, 0, 0),
        ofColor(0, 0, 255),
        ofColor(255, 127, 0),
        ofColor(255, 255, 0)
    });
    
    m_masked_gradient.enableIndices();
    m_masked_gradient.addIndices({
        0, 1, 3,
        1, 2, 3
    });
}


void ofApp::setupBackgroundGradientMesh() {
    m_bg_gradient.setMode(OF_PRIMITIVE_TRIANGLES);
    
    m_bg_gradient.addVertex(ofVec3f(0.f, 0.f, 0.f));
    m_bg_gradient.addVertex(ofVec3f(ofGetWidth() - GRADIENT_OFFSET * 2, 0.f, 0.f));
    m_bg_gradient.addVertex(ofVec3f(ofGetWidth() - GRADIENT_OFFSET * 2, ofGetHeight() - GRADIENT_OFFSET * 2, 0.f));
    m_bg_gradient.addVertex(ofVec3f(0.f, ofGetHeight() - GRADIENT_OFFSET * 2, 0.f));
    
    m_bg_gradient.enableColors();
    m_bg_gradient.addColors({ofColor(66), ofColor(33), ofColor(33), ofColor(66)});
    
    m_bg_gradient.enableIndices();
    m_bg_gradient.addIndices({
        0, 1, 3,
        1, 2, 3
    });
}

