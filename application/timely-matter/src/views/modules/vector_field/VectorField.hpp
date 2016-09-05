#pragma once

#include "ofMain.h"
#include "VectorFieldMark.hpp"


namespace timelymatter
{

    class VectorField {
        
        void m_setupMarks();
        void onMaxEdgeForceChanged(float& value);
        void onMaxFieldForceChanged(float& value);
        
        unsigned int m_field_width, m_field_height;
        unsigned int m_input_width, m_input_height;
        unsigned int m_subdivision_x, m_subdivision_y;
        float m_field_inc_x, m_field_inc_y;
        float m_input_inc_x, m_input_inc_y;
        unsigned int m_marks_per_row, m_marks_per_column;
        unsigned int m_average_datum;
        vector<VectorFieldMark> m_marks;
        ofParameterGroup m_params;
        ofParameter<float> m_edge_force;
        ofParameter<float> m_field_force;
        ofParameter<float> m_attract_threshold;
        ofParameter<bool> m_show_marks;
        ofParameter<bool> m_show_values;
        ofParameter<bool> m_show_vectors;
    public:
        void setup(const unsigned int width, const unsigned int height, const unsigned int subdivision);
        void setup(const unsigned int width, const unsigned int height, const unsigned int subdivisionX, const unsigned int subdivisionY);
        void setup(const unsigned int fieldWidth, const unsigned int fieldHeight, const unsigned int inputWidth, const unsigned int inputHeight, const unsigned int subdivision);
        void setup(const unsigned int fieldWidth, const unsigned int fieldHeight, const unsigned int inputWidth, const unsigned int inputHeight, const unsigned int subdivisionX, const unsigned int subdivisionY);
        void update(const ofPixels &pixels);
        void draw();
        const ofVec3f& getForceForPosition(const ofVec3f& position) const;
        const ofVec3f getMeterPointForPosition(const ofVec3f& position) const;
        ofParameterGroup& getParams() { return m_params; };
        const unsigned int getAverageDatum() const { return m_average_datum; };
        const float getMaxEdgeForce() const { return m_edge_force; };
        const float getMaxFieldForce() const { return m_field_force; };
    };

}