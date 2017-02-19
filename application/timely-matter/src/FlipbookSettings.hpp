#pragma once

#include "ofMain.h"

#define SETTINGS_FILE "flipbook_settings.xml"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class FlipbookSettings {
        
        // private constructor
        FlipbookSettings() {}
        
        // settings to be loaded from XML file
        ofxXmlSettings m_settings;
        
        // flag to check if file could be loaded
        bool m_loaded;
        
        // params defined in external file
        unsigned int m_total_pages;
        unsigned int m_capture_rate;
        
        // function to parse xml
        void parseXml() {
            m_settings.pushTag("flipbook_settings");
            m_total_pages = m_settings.getValue("total_pages", 10);
            m_capture_rate = m_settings.getValue("capture_rate", 6);
            m_settings.popTag();
        }
        
    public:
        // static method to retrieve singleton instance
        static FlipbookSettings & get() {
            static FlipbookSettings instance;
            return instance;
        }
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        FlipbookSettings(FlipbookSettings const&) = delete;
        void operator=(FlipbookSettings const&) = delete;
        
        // main function to load settings from xml file
        bool load() {
            m_loaded = m_settings.load(SETTINGS_FILE);
            
            if (m_loaded) {
                parseXml();
            }
            
            return m_loaded;
        }
        
        const bool & isLoaded() {
            return m_loaded;
        }
        
        const unsigned int & getTotalPages() {
            return m_total_pages;
        }
        
        const unsigned int & getCaptureRate() {
            return m_capture_rate;
        }
        
    };
}
