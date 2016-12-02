#include "ofMain.h"
#include "ofxXmlSettings.h"

#define APP_CONFIG_SETTINGS_FILE "AppConfig.xml"


namespace timelymatter {
    
    // Singleton class
    // Proposed implementation adapted from here:
    // http://stackoverflow.com/questions/1008019/c-singleton-design-pattern#1008289
    class AppConfig {
        
        // private constructor
        AppConfig() {}
        // settings to be loaded from XML file
        ofxXmlSettings m_settings;
        // flag to check if file could be loaded
        bool m_loaded;
        
        // variable to store setting values
        float m_kinect_crop_ratio;
        int m_projector_width;
        int m_projector_height;
        float m_projector_render_ratio;
        int m_projector_render_width;
        int m_projector_render_height;
        int m_particle_system_count;
        float m_particle_system_min_radius;
        float m_particle_system_max_radius;
        int m_marching_squares_columns;
        int m_marching_squares_rows;
        
        void parseXml() {
            m_settings.pushTag("AppConfig");
            
            // parse Kinect values
            m_settings.pushTag("kinect");
            m_kinect_crop_ratio = m_settings.getValue("crop_ratio", 0.0);
            m_settings.popTag();
            
            // parse projector values
            m_settings.pushTag("projector");
            m_projector_width = m_settings.getValue("width", 0);
            m_projector_height = m_settings.getValue("height", 0);
            m_projector_render_ratio = m_settings.getValue("render_ratio", 0.0);
            m_projector_render_width = m_projector_width * m_projector_render_ratio;
            m_projector_render_height = m_projector_height * m_projector_render_ratio;
            m_settings.popTag();
            
            // parse particle system values
            m_settings.pushTag("particle_system");
            m_particle_system_count = m_settings.getValue("count", 0);
            m_particle_system_min_radius = m_settings.getValue("min_radius", 0);
            m_particle_system_max_radius = m_settings.getValue("max_radius", 0.0);
            m_settings.popTag();
            
            // parse marching squares values
            m_settings.pushTag("marching_squares");
            m_marching_squares_columns = m_settings.getValue("columns", 0);
            m_marching_squares_rows = m_settings.getValue("rows", 0);
            m_settings.popTag();
            
            m_settings.popTag();
        }
        
        
    public:
        // static method to retrieve singleton instance
        static AppConfig& get() {
            static AppConfig instance;
            return instance;
        }
        
        // remove copy constructor and and copy assingnment operator - C++ 11 style
        AppConfig(AppConfig const&) = delete;
        void operator=(AppConfig const&) = delete;
        
        // main function to load settings from xml file
        bool load() {
            m_loaded = m_settings.load(APP_CONFIG_SETTINGS_FILE);
            if (m_loaded) {
                parseXml();
            }
            return m_loaded;
        }
        
        // methods to retrieve values from settings file
        const float& getKinectCropRatio() {
            return m_kinect_crop_ratio;
        }
        const int& getProjectorWidth() {
            return m_projector_width;
        }
        const int& getProjectorHeight() {
            return m_projector_height;
        }
        const float& getProjectorRenderRatio() {
            return m_projector_render_ratio;
        }
        const int& getProjectorRenderWidth() {
            return m_projector_render_width;
        }
        const int& getProjectorRenderHeight() {
            return m_projector_render_height;
        }
        const int& getParticleSystemCount() {
            return m_particle_system_count;
        }
        const float& getParticleSystemMinRadius() {
            return m_particle_system_min_radius;
        }
        const float& getParticleSystemMaxRadius() {
            return m_particle_system_max_radius;
        }
        const int& getMarchingSquaresColumns() {
            return m_marching_squares_columns;
        }
        const int& getMarchingSquaresRows() {
            return m_marching_squares_rows;
        }
    
    };

}