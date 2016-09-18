#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
    ofGLFWWindowSettings settings;
//    settings.setGLVersion(3, 2); // OpenGL 3.2, #version 150
    settings.setGLVersion(3, 3); // OpenGL 3.3, #version 330
    settings.width = 1024;
    settings.height = 768;
    settings.resizable = false;
    settings.title = "Programmable Geometry Shader Example";
    
    ofCreateWindow(settings);
    
    if (!ofIsGLProgrammableRenderer()) {
        ofLog() << "graphics card does not support programmable shaders";
        return 1;
    }
    
    ofRunApp(new ofApp());
    
    ofLog() << "See ya!";
}
