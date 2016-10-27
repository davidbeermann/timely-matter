#include "PostFxQueue.hpp"


void PostFxQueue::init(unsigned int width, unsigned int height) {
    if (width == 0 || height == 0) {
        ofLogError() << "Width and height must be larger than 0!";
        return;
    }
    
    m_width = width;
    m_height = height;
    
    m_output.allocate(width, height, GL_RGBA, 8);
    clear();
    
    if (m_modules.size() > 0) {
        for (unsigned int i = 0; i < m_modules.size(); ++i) {
            m_modules[i]->init(width, height);
        }
    }
}


void PostFxQueue::add(PostFxModule& module) {
    add(&module);
}


void PostFxQueue::add(PostFxModule* module) {
    unsigned int index = m_modules.size();
    m_modules.push_back(module);
    
    if (m_width != 0 && m_height != 0) {
        m_modules[index]->init(m_width, m_height);
    }
}


void PostFxQueue::clear() {
    m_output.begin();
    ofClear(0.f);
    m_output.end();
}


void PostFxQueue::render() {
    if (m_modules.size() > 0) {
        for (unsigned int i = 0; i < m_modules.size(); ++i) {
            m_modules[i]->render(m_output);
        }
    }
}


ofFbo& PostFxQueue::getOutput() {
    return m_output;
}

