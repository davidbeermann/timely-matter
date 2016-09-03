#include "ofMain.h"
#include "ofApp.h"


int main( ){
    // create window for application
    ofGLFWWindowSettings settings;
    settings.title = "Timely Matter";
    settings.width = 1320;
    settings.height = 1000;
    settings.resizable = true;
//    settings.setGLVersion(3, 2); // OpenGL 3.2 - GLSL #version 150
    settings.setGLVersion(3, 3); // OpenGL 3.3 - GLSL #version 330
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
