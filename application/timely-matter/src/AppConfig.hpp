#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "Constants.hpp"

#define DEFAULT_SETTINGS_FILE "AppConfig.xml"
#define FLIPBOOK_SETTINGS_FILE "AppConfigFlipbook.xml"


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
        int m_output_projector_width;
        int m_output_projector_height;
        int m_output_buffer_width;
        int m_output_buffer_height;
        int m_kinect_crop_buffer_width;
        int m_kinect_crop_buffer_height;
        int m_vector_field_subdivision_x;
        int m_vector_field_subdivision_y;
        int m_particle_system_count;
        float m_particle_system_min_radius;
        float m_particle_system_max_radius;
        int m_marching_squares_columns;
        int m_marching_squares_rows;
        ofColor m_background_color;
        ofColor m_background_clear_color;
        ofColor m_metaballs_color;
        
        void parseXml() {
            m_settings.pushTag("AppConfig");
            
            // parse output values
            m_settings.pushTag("output");
            m_output_projector_width = m_settings.getValue("projector_width", 0);
            m_output_projector_height = m_settings.getValue("projector_height", 0);
            m_output_buffer_width = m_settings.getValue("buffer_width", 0);
            m_output_buffer_height = m_settings.getValue("buffer_height", 0);
            m_settings.popTag();
            
            // parse Kinect values
            m_settings.pushTag("kinect");
            m_kinect_crop_buffer_width = m_settings.getValue("crop_buffer_width", 0);
            m_kinect_crop_buffer_height = m_settings.getValue("crop_buffer_height", 0);
            m_settings.popTag();
            
            // parse vector field values
            m_settings.pushTag("vector_field");
            m_vector_field_subdivision_x = m_settings.getValue("subdivision_x", 0);
            m_vector_field_subdivision_y = m_settings.getValue("subdivision_y", 0);
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
            
            m_settings.pushTag("colors");
            parseHsb(m_background_color, "background");
            parseHsb(m_metaballs_color, "metaballs");
            m_background_clear_color.set(m_background_color);
            m_background_clear_color.a = 0.f;
            m_settings.popTag();
            
            m_settings.popTag();
        }
        
        void parseHsb(ofColor & color, string attribute) {
            double h = m_settings.getAttribute(attribute, "hue", 0.0);
            double s = m_settings.getAttribute(attribute, "saturation", 0.0);
            double b = m_settings.getAttribute(attribute, "brightness", 0.0);
            double a = m_settings.getAttribute(attribute, "alpha", 1.0);
            color.setHsb(h * 255.f, s * 255.f, b * 255.f, a * 255.f);
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
            if (FLIPBOOK_ENABLED) {
                m_loaded = m_settings.load(FLIPBOOK_SETTINGS_FILE);
            } else {
                m_loaded = m_settings.load(DEFAULT_SETTINGS_FILE);
            }
            
            if (m_loaded) {
                parseXml();
            }
            
            return m_loaded;
        }
        
        const bool & isLoaded() {
            return m_loaded;
        }
        
        // methods to retrieve values from settings file
        const int& getOutputProjectorWidth() {
            return m_output_projector_width;
        }
        const int& getOutputProjectorHeight() {
            return m_output_projector_height;
        }
        const int& getOutputBufferWidth() {
            return m_output_buffer_width;
        }
        const int& getOutputBufferHeight() {
            return m_output_buffer_height;
        }
        
        const int& getKinectCropBufferWidth() {
            return m_kinect_crop_buffer_width;
        }
        const int& getKinectCropBufferHeight() {
            return m_kinect_crop_buffer_height;
        }
        
        const int& getVectorFieldSubdivisionX() {
            return m_vector_field_subdivision_x;
        }
        const int& getVectorFieldSubdivisionY() {
            return m_vector_field_subdivision_y;
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
        
        const ofColor & getBackgroundColor() {
            return m_background_color;
        }
        const ofColor & getBackgroundClearColor() {
            return m_background_clear_color;
        }
        const ofColor & getMetaballsColor() {
            return m_metaballs_color;
        }
    
    };

}