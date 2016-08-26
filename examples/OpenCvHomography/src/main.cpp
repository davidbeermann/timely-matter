#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    ofGLFWWindowSettings settings;
    settings.width = 1290;
    settings.height = 620;
    settings.setGLVersion(3, 3);
    settings.windowMode = OF_WINDOW;
    settings.title = "Homographic Transformation Demo";
    ofCreateWindow(settings);

    ofRunApp(new ofApp());
}
