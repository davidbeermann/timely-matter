#include "ofMain.h"
#include "ofApp.h"
#include "ofController.hpp"


int main( ){
    // create window for controller application
    ofGLFWWindowSettings controllerSettings;
    controllerSettings.title = "Controller";
    controllerSettings.width = 690;
    controllerSettings.height = 800;
    controllerSettings.resizable = false;
    controllerSettings.setGLVersion(3, 3); // OpenGL 3.3 #version 330
    shared_ptr<ofAppBaseWindow> controllerWindow = ofCreateWindow(controllerSettings);
    
    // create window for main application
    ofGLFWWindowSettings appSettings;
    appSettings.title = "Application";
    appSettings.width = 1024;
    appSettings.height = 768;
    appSettings.resizable = true;
    appSettings.setGLVersion(3, 3); // OpenGL 3.3 #version 330
    // SHARE CONTEXT!
    // enables rendering of elements instanciated in ofApp in ofController
    appSettings.shareContextWith = controllerWindow;
    shared_ptr<ofAppBaseWindow> appWindow = ofCreateWindow(appSettings);
    
    // CREATE APPLICATIONS
    // use shared pointers in order to pass ofApp instance into ofController instance
    shared_ptr<ofController> controller(new ofController());
    shared_ptr<ofApp> app(new ofApp());
    
    // Setup link between windows
    controller->mainApp = app;
    
    // Link apps to windows
    ofRunApp(controllerWindow, controller);
    ofRunApp(appWindow, app);
    
    // Kick off main loop
    ofRunMainLoop();
    
    // be nice once the main loop ends and the application exits. :)
    ofLog() << "Goodbye!";
}
