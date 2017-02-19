#include "ofMain.h"
#include "ofApp.h"
#include "Constants.hpp"

using namespace timelymatter;


int main( ){
    if (FLIPBOOK_ENABLED) {
        ofLog() << "~*~*~*~*~*~*~*~*~*";
        ofLog() << " FLIPBOOK VERSION ";
        ofLog() << "~*~*~*~*~*~*~*~*~*";
    } else {
        ofLog() << "~*~*~*~*~*~*~*~*~*~*~*";
        ofLog() << " INSTALLATION VERSION ";
        ofLog() << "~*~*~*~*~*~*~*~*~*~*~*";
    }
    
    // create window for application
    ofGLFWWindowSettings settings;
    settings.title = "Timely Matter";
//    settings.setGLVersion(3, 2); // OpenGL 3.2 - GLSL #version 150
    settings.setGLVersion(3, 3); // OpenGL 3.3 - GLSL #version 330
    if (FLIPBOOK_ENABLED) {
        // DIN Lang portrait format aspect ratio
        settings.width = 360;
        settings.height = 700;
        settings.resizable = false;
    } else {
        settings.width = 1000;
        settings.height = 700;
        settings.resizable = true;
    }
    shared_ptr<ofAppBaseWindow> appWindow = ofCreateWindow(settings);
    
    // create application
    shared_ptr<ofApp> app(new ofApp());
    
    // Link apps to windows
    ofRunApp(appWindow, app);
    
    // Kick off main loop
    ofRunMainLoop();
    
    // be nice once the main loop ends and the application exits. :)
    ofLog() << "Goodbye!";
}
