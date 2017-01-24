#include "PdfRenderer.hpp"
#include "StringUtils.hpp"

#define SAVE_FILE_MODE ofCairoRenderer::PDF

using namespace timelymatter;


PdfRenderer::PdfRenderer() {
    // register listener for keyboard events
    ofRegisterKeyEvents(this);
}


void PdfRenderer::setup(unsigned int max_file_count, unsigned int capture_rate) {
    
    m_max_file_count = max_file_count;
    m_capture_rate = capture_rate;
    
    // create unique folder name for each time the application runs
    m_files_folder = padNumber(ofGetYear(), 4);
    m_files_folder += padNumber(ofGetMonth(), 2);
    m_files_folder += padNumber(ofGetDay(), 2);
    m_files_folder += "-";
    m_files_folder += padNumber(ofGetHours(), 2);
    m_files_folder += padNumber(ofGetMinutes(), 2);
    m_files_folder += padNumber(ofGetSeconds(), 2);
    
    m_file_count = 0;
    m_frame_count = 0;
    m_capture_activated = false;
    m_write_file = false;
    
}


void PdfRenderer::update() {
    
    // automatically stop capturing after all files are written
    if (m_file_count >= m_max_file_count) {
        m_capture_activated = false;
        m_file_count = 0;
        ofLog() << "All " << m_max_file_count << " files created.";
    }
    
    // always stop writing files after one update cycle
    if (m_write_file) {
        m_frame_count = 0;
        m_write_file = false;
    }
    
    // set write file flag according to capture rate
    if (m_capture_activated) {
        m_write_file = (++m_frame_count >= m_capture_rate);
    }
    
}



void PdfRenderer::begin() {
    
    // create new cairo renderer instance
    m_renderer = ofCairoRenderer();
    
    // increment file count
    m_file_count++;
    
    // SET FILE NAME
    // -------------
    // padding the file name count with zeros
    // ensures that the sequence is preserved during placement in InDesign
    string file_name = "frame-" + padNumber(m_file_count, to_string(m_max_file_count).length());
    
    // setup renderer
    if (SAVE_FILE_MODE == ofCairoRenderer::PDF) {
        m_renderer.setup(m_files_folder+"/"+file_name+".pdf", ofCairoRenderer::PDF);
    } else if(SAVE_FILE_MODE == ofCairoRenderer::SVG) {
        m_renderer.setup(m_files_folder+"/"+file_name+".svg", ofCairoRenderer::SVG);
    } else {
        ofLog() << "Unknown file mode.";
        return;
    }
    
    m_renderer.viewport(ofRectangle(0, 0, ofGetWidth(), ofGetHeight()));
    m_renderer.setBlendMode(OF_BLENDMODE_ALPHA);
    m_renderer.setBackgroundColor(ofColor(0,0,0,0));
    m_renderer.setFillMode(OF_FILLED);
    
}


void PdfRenderer::end() {
    
    // close renderer
    m_renderer.close();
    
}


void PdfRenderer::keyPressed(ofKeyEventArgs& args) {
    if (args.key == 'P') {
        m_capture_activated = !m_capture_activated;
    }
}

