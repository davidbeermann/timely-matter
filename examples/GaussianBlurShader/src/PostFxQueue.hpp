#pragma once

#include "ofMain.h"
#include "PostFxModule.hpp"


class PostFxQueue {
    
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    vector<PostFxModule*> m_modules;
    ofFbo m_output;
    
public:
    void init(unsigned int width, unsigned int height);
    void add(PostFxModule& module);
    void add(PostFxModule* module);
    void clear();
    void render();
    ofFbo& getOutput();

};