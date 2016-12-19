#include "OscRenderControls.hpp"

#define CONFIG_FILE "OscConfig.xml"

#define ADDR_INPUT_VISIBLE "/tm/input/show"
#define ADDR_INPUT_ALPHA "/tm/input/alpha"
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
#define ADDR_MB_WIREFRAMEALPHA "/tm/metaballs/wireframealpha"
#define ADDR_MB_FITNESS "/tm/metaballs/fitness"
#define ADDR_MB_THRESHOLD "/tm/metaballs/threshold"
#define ADDR_MB_DAMPENING "/tm/metaballs/dampening"

using namespace timelymatter;


void OscRenderControls::sendInitialStatus() {
    ofxOscMessage msg;
    
    msg.setAddress(ADDR_INPUT_VISIBLE);
    msg.addBoolArg(m_params.getInputVisible());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_INPUT_ALPHA);
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
    
    msg.setAddress(ADDR_PS_CORESALPHA);
    msg.addFloatArg(m_params.getParticleCoresAlpha());
    m_sender.sendMessage(msg);
    msg.clear();
    
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
    
    msg.setAddress(ADDR_MB_WIREFRAMEALPHA);
    msg.addFloatArg(m_params.getMetaballsWireframeAlpha());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_FITNESS);
    msg.addFloatArg(m_params.getMetaballsFitness());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_THRESHOLD);
    msg.addFloatArg(m_params.getMetaballsThreshold());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_MB_DAMPENING);
    msg.addFloatArg(m_params.getMetaballsDampening());
    m_sender.sendMessage(msg);
    msg.clear();
}


void OscRenderControls::m_onSetup() {
    
    bool config_loaded = m_config.load(CONFIG_FILE);
    if (config_loaded) {
        m_config.pushTag("OscConfig");
        
        // configure sender interface
        string sender_address;
        unsigned int sender_port;
        
        m_config.pushTag("sender");
        sender_address = m_config.getValue("address", "");
        sender_port = m_config.getValue("port", 0);
        m_config.popTag();
        
        if (sender_address != "" && sender_port != 0) {
            m_sender.setup(sender_address, sender_port);
            sendInitialStatus();
        }
        
        // configure receiver interface
        unsigned int receiver_port;
        
        m_config.pushTag("receiver");
        receiver_port = m_config.getValue("port", 0);
        m_config.popTag();
        
        if (receiver_port != 0) {
            m_receiver.setup(receiver_port);
        }
        
        m_config.popTag();
        
    } else {
        ofLogError() << "OSC configurtation could not be loaded!";
    }
    
}


void OscRenderControls::m_onUpdate() {
    
    // check for waiting messages
    while (m_receiver.hasWaitingMessages()) {
        
        // get the next message
        ofxOscMessage msg;
        m_receiver.getNextMessage(msg);
        
        // check if depth alpha has changed
        if (msg.getAddress() == ADDR_INPUT_VISIBLE) {
            m_params.getInputVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_INPUT_ALPHA) {
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
            m_params.getParticleCoresAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_MB_INFILL) {
            m_params.getMetaballsInfill() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_SHOWMESH) {
            m_params.getMetaballsMeshVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_MESHALPHA) {
            m_params.getMetaballsMeshAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_MB_SHOWWIREFRAME) {
            m_params.getMetaballsWireframeVisible() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_WIREFRAMEALPHA) {
            m_params.getMetaballsWireframeAlpha() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_MB_INTERPOLATE) {
            m_params.getMetaballsInterpolate() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_MB_FITNESS) {
            m_params.getMetaballsFitness() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_MB_THRESHOLD) {
            m_params.getMetaballsThreshold() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_MB_DAMPENING) {
            m_params.getMetaballsDampening() = msg.getArgAsFloat(0);
        }
    }
    
}

