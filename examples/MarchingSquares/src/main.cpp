#include "ofMain.h"
#include "ofApp.h"


int main( ){
	
    ofGLFWWindowSettings settings;
    settings.setGLVersion( 3, 2 );
    settings.width = 1024;
    settings.height = 768;
    settings.resizable = true;
    settings.title = "Marching Squares Example";
    
    shared_ptr<ofAppBaseWindow> window = ofCreateWindow(settings);
    shared_ptr<ofBaseApp> app(new ofApp());
    
    ofRunApp( window, app );
    
    ofRunMainLoop();
    
    ofLog() << "Goodbye!";

}
