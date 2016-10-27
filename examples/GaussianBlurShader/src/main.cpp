#include "ofMain.h"
#include "ofApp.h"


int main( ){
    
    ofLog() << "Hello!";
    
    ofGLFWWindowSettings settings;
    settings.setGLVersion(3, 3); // #version 330
    settings.width = 900;
    settings.height = 600;
    settings.resizable = true;
    settings.title = "Gaussian Blur Shader Example";
    
    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<ofBaseApp> app(new ofApp());
    
    ofRunApp(window, app);
    
    ofRunMainLoop();
    
    ofLog() << "Goodbye.";
    
}
