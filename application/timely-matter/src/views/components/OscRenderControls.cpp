#include "OscRenderControls.hpp"

#define PORT 12345

using namespace timelymatter;


void OscRenderControls::m_onSetup() {
    m_receiver.setup(PORT);
}


void OscRenderControls::m_onUpdate() {
    
    // check for waiting messages
    while (m_receiver.hasWaitingMessages()) {
        
        // get the next message
        ofxOscMessage msg;
        m_receiver.getNextMessage(msg);
        
        // check if depth alpha has changed
        if (msg.getAddress() == "/tm/depthvisible") {
            m_params.getInputVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/depthalpha") {
            m_params.getInputAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == "/tm/particlesystem/update") {
            m_params.getParticlesUpdate() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/particlesystem/showareas") {
            m_params.getParticleAreasVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/particlesystem/showcores") {
            m_params.getParticleCoresVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/particlesystem/areasalpha") {
            m_params.getParticleAreasAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == "/tm/particlesystem/coresalpha") {
            //TODO
//            m_params.getInputAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == "/tm/metaballs/showmesh") {
            m_params.getMetaballsMeshVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/metaballs/showwireframe") {
            m_params.getMetaballsWireframeVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/metaballs/interpolate") {
            m_params.getMetaballsInterpolate() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/metaballs/infill") {
            m_params.getMetaballsInfill() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == "/tm/metaballs/meshalpha") {
            m_params.getMetaballsMeshAlpha() = msg.getArgAsFloat(0);
        }
    }
    
}

