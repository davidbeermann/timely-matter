#include "SoundControls.hpp"

#define CONFIG_FILE "OscConfig.xml"

#define ADDR_START "/tm/sound/start"
#define ADDR_RESTART "/tm/sound/restart"
#define ADDR_VOLUME "/tm/sound/volume"
#define ADDR_RANDOM "/tm/sound/random"
#define ADDR_SOUND1 "/tm/sound/1"
#define ADDR_SOUND2 "/tm/sound/2"
#define ADDR_SOUND3 "/tm/sound/3"
#define ADDR_SOUND4 "/tm/sound/4"
#define ADDR_SOUND5 "/tm/sound/5"
#define ADDR_SOUND6 "/tm/sound/6"
#define ADDR_SOUND7 "/tm/sound/7"
#define ADDR_SOUND8 "/tm/sound/8"
#define ADDR_SOUND9 "/tm/sound/9"


void SoundControls::sendInitialStatus() {
    ofxOscMessage msg;
    
    msg.setAddress(ADDR_START);
    msg.addBoolArg(m_params.getPlaying());
    m_sender.sendMessage(msg);
    msg.clear();
    
    msg.setAddress(ADDR_VOLUME);
    msg.addFloatArg(m_params.getVolume());
    m_sender.sendMessage(msg);
    msg.clear();
}


void SoundControls::setup() {
    
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
        } else {
            ofLogError() << "OSC sender interface could not be setup!";
        }
        
        // configure receiver interface
        unsigned int receiver_port;
        
        m_config.pushTag("receiver");
        receiver_port = m_config.getValue("port", 0);
        m_config.popTag();
        
        if (receiver_port != 0) {
            m_receiver.setup(receiver_port);
        } else {
            ofLogError() << "OSC receiver interface could not be setup!";
        }
        
        m_config.popTag();
        
    } else {
        ofLogError() << "OSC configurtation could not be loaded!";
    }
    
}


void SoundControls::update() {
    
    // check for waiting messages
    while (m_receiver.hasWaitingMessages()) {
        
        // get the next message
        ofxOscMessage msg;
        m_receiver.getNextMessage(msg);
        
        // check if depth alpha has changed
        if (msg.getAddress() == ADDR_START) {
            m_params.getPlaying() = msg.getArgAsBool(0);
        }
        else if (msg.getAddress() == ADDR_VOLUME) {
            m_params.getVolume() = msg.getArgAsFloat(0);
        }
        else if (msg.getAddress() == ADDR_RANDOM) {
            m_params.triggerRandom(msg.getArgAsBool(0));
        }
    }
    
}

