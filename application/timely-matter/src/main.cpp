#include "ofMain.h"
#include "ofApp.h"
#include "ofController.hpp"


int main( ){
    ofGLFWWindowSettings settings;
    
    // create window for controller application
    //    ofGLFWWindowSettings controllerSettings;
    settings.title = "Controller";
    settings.width = 690;
    settings.height = 800;
    settings.resizable = false;
    settings.setGLVersion(3, 2); // OpenGL 3.2 - GLSL #version 150
//    settings.setGLVersion(3, 3); // OpenGL 3.3 - GLSL #version 330
    shared_ptr<ofAppBaseWindow> controllerWindow = ofCreateWindow(settings);
    
    // create window for main application
    //    ofGLFWWindowSettings appSettings;
    settings.title = "Application";
    settings.width = 1024;
    settings.height = 768;
    settings.resizable = true;
    settings.setGLVersion(3, 2); // OpenGL 3.2 - GLSL #version 150
//    settings.setGLVersion(3, 3); // OpenGL 3.3 - GLSL #version 330
    // SHARE CONTEXT!
    // enables rendering of elements instanciated in ofApp in ofController
    // and strangely also the rendering in ofApp... i.e. fbo and shaders
    settings.shareContextWith = controllerWindow;
    shared_ptr<ofAppBaseWindow> appWindow = ofCreateWindow(settings);
    
    // CREATE APPLICATIONS
    // use shared pointers in order to pass ofApp instance into ofController instance
    shared_ptr<ofApp> app(new ofApp());
    shared_ptr<ofController> controller(new ofController());
    
    // Setup link between windows
    controller->app_sptr = app;
    
    // Link apps to windows
    ofRunApp(controllerWindow, controller);
    ofRunApp(appWindow, app);
    
    // Kick off main loop
    ofRunMainLoop();
    
    // be nice once the main loop ends and the application exits. :)
    ofLog() << "Goodbye!";
}
