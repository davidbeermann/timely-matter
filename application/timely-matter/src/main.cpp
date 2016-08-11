#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    // setup window and OpenGL context
    ofGLWindowSettings settings;
     // sets the OpenGL version to 3.2; GLSL #version 150
    settings.setGLVersion(3, 2);
    settings.width = 1280;
    settings.height = 720;
    ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
