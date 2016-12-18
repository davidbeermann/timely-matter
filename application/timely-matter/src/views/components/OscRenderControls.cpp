#include "OscRenderControls.hpp"

#define RECEIVE_PORT 9999
#define SEND_PORT 9998
#define SEND_HOST "192.168.178.33"

#define ADDR_DEPTH_VISIBLE "/tm/depthvisible"
#define ADDR_DEPTH_ALPHA "/tm/depthalpha"
#define ADDR_PS_UPDATE "/tm/particlesystem/update"
#define ADDR_PS_SHOWAREAS "/tm/particlesystem/showareas"
#define ADDR_PS_SHOWCORES "/tm/particlesystem/showcores"
#define ADDR_PS_AREASALPHA "/tm/particlesystem/areasalpha"
#define ADDR_PS_CORESALPHA "/tm/particlesystem/coresalpha"
#define ADDR_MB_SHOWMESH "/tm/metaballs/showmesh"
#define ADDR_MB_SHOWWIREFRAME "/tm/metaballs/showwireframe"
#define ADDR_MB_INTERPOLATE "/tm/metaballs/interpolate"
#define ADDR_MB_INFILL "/tm/metaballs/infill"
#define ADDR_MB_MESHALPHA "/tm/metaballs/meshalpha"

using namespace timelymatter;


void OscRenderControls::m_onSetup() {
    // setup receiver
    m_receiver.setup(RECEIVE_PORT);
    
    // setup sender
    m_sender.setup(SEND_HOST, SEND_PORT);
    
    // send out initial states
    ofxOscMessage msg;
    
    msg.setAddress(ADDR_DEPTH_VISIBLE);
    msg.addBoolArg(m_params.getInputVisible());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_DEPTH_ALPHA);
    msg.addFloatArg(m_params.getInputAlpha());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_PS_UPDATE);
    msg.addBoolArg(m_params.getParticlesUpdate());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_PS_SHOWAREAS);
    msg.addBoolArg(m_params.getParticleAreasVisible());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_PS_SHOWCORES);
    msg.addBoolArg(m_params.getParticleCoresVisible());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_PS_AREASALPHA);
    msg.addFloatArg(m_params.getParticleAreasAlpha());
    m_sender.sendMessage(msg);
    msg.clear();
    
//    msg.setAddress(ADDR_PS_CORESALPHA);
//    msg.addFloatArg(m_params.getInputAlpha());
//    m_sender.sendMessage(msg);
//    msg.clear();
    
    msg.setAddress(ADDR_MB_SHOWMESH);
    msg.addBoolArg(m_params.getMetaballsMeshVisible());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_SHOWWIREFRAME);
    msg.addBoolArg(m_params.getMetaballsWireframeVisible());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_INTERPOLATE);
    msg.addBoolArg(m_params.getMetaballsInterpolate());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_INFILL);
    msg.addBoolArg(m_params.getMetaballsInfill());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_MESHALPHA);
    msg.addFloatArg(m_params.getMetaballsMeshAlpha());
    m_sender.sendMessage(msg);
    msg.clear();
    
}


void OscRenderControls::m_onUpdate() {
    
    // check for waiting messages
    while (m_receiver.hasWaitingMessages()) {
        
        // get the next message
        ofxOscMessage msg;
        m_receiver.getNextMessage(msg);
        
        // check if depth alpha has changed
        if (msg.getAddress() == ADDR_DEPTH_VISIBLE) {
            m_params.getInputVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_DEPTH_ALPHA) {
            m_params.getInputAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_PS_UPDATE) {
            m_params.getParticlesUpdate() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_PS_SHOWAREAS) {
            m_params.getParticleAreasVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_PS_SHOWCORES) {
            m_params.getParticleCoresVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_PS_AREASALPHA) {
            m_params.getParticleAreasAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_PS_CORESALPHA) {
            //TODO
//            m_params.getInputAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_MB_SHOWMESH) {
            m_params.getMetaballsMeshVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_SHOWWIREFRAME) {
            m_params.getMetaballsWireframeVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_INTERPOLATE) {
            m_params.getMetaballsInterpolate() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_INFILL) {
            m_params.getMetaballsInfill() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_MESHALPHA) {
            m_params.getMetaballsMeshAlpha() = msg.getArgAsFloat(0);
        }
    }
    
}

