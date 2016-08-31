#pragma once

#include "ofMain.h"
#include "VectorFieldMark.h"

class VectorField {
    
    void m_setupMarks();
    void onMaxEdgeForceChanged(float& value);
    void onMaxFieldForceChanged(float& value);
    
    unsigned int m_field_width, m_field_height;
    unsigned int m_input_width, m_input_height;
    unsigned int m_subdivision_x, m_subdivision_y;
    float m_field_inc_x, m_field_inc_y;
    float m_input_inc_x, m_input_inc_y;
    unsigned int mMarksPerRow, mMarksPerColumn;
    vector<VectorFieldMark> mMarks;
    ofParameterGroup mGuiParams;
    ofParameter<float> mMaxEdgeForce;
    ofParameter<float> mMaxFieldForce;
    ofParameter<bool> mGuiDebugMeterPoints;
    ofParameter<bool> mGuiDebugMeterValues;
    ofParameter<bool> mGuiDebugVector;
public:
    void setup(const unsigned int width, const unsigned int height, const unsigned int subdivision);
    void setup(const unsigned int width, const unsigned int height, const unsigned int subdivisionX, const unsigned int subdivisionY);
    void setup(const unsigned int fieldWidth, const unsigned int fieldHeight, const unsigned int inputWidth, const unsigned int inputHeight, const unsigned int subdivision);
    void setup(const unsigned int fieldWidth, const unsigned int fieldHeight, const unsigned int inputWidth, const unsigned int inputHeight, const unsigned int subdivisionX, const unsigned int subdivisionY);
    void update(const ofPixels &pixels);
    void draw();
    const ofVec3f& getForceForPosition(const ofVec3f& position) const;
    const ofVec3f getMeterPointForPosition(const ofVec3f& position) const;
    const ofParameterGroup& getGuiParams();
};