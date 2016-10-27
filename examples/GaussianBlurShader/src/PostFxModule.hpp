#pragma once

#include "ofMain.h"


class PostFxModule {
    
protected:
    virtual void doInit(unsigned int width, unsigned int height) = 0;
    virtual void doRender(ofFbo& input) = 0;

public:
    void init(unsigned int width, unsigned int height) {
        doInit(width, height);
    }
    void render(ofFbo& input) {
        doRender(input);
    }

};