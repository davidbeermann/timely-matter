#pragma once

#include "ofMain.h"


namespace timelymatter {

    class PdfRenderer {
    
        string m_files_folder;
        unsigned int m_max_file_count;
        unsigned int m_capture_rate;
        unsigned int m_frame_count;
        unsigned int m_file_count;
        bool m_capture_activated;
        bool m_write_file;
        ofCairoRenderer m_renderer;
        
    public:
        PdfRenderer();
        
        void setup(unsigned int max_file_count, unsigned int capture_rate);
        void update();
        void begin();
        void end();
        
        // key event listener methods
        void keyPressed(ofKeyEventArgs& args);
        void keyReleased(ofKeyEventArgs& args) {};
        
        bool const & isWritingFile() {
            return m_write_file;
        }
        
        ofCairoRenderer & get() {
            return m_renderer;
        }
    
    };
    
}