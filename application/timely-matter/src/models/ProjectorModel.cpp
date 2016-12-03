#include "ProjectorModel.hpp"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

using namespace timelymatter;


ProjectorModel::ProjectorModel() {
    // set default values
    m_output.set(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
    m_buffer.set(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}


ProjectorModel& ProjectorModel::get() {
    static ProjectorModel model;
    return model;
}


const unsigned int ProjectorModel::getOutputWidth() const {
    return m_output.getWidth();
}


const unsigned int ProjectorModel::getOutputHeight() const {
    return m_output.getHeight();
}


const ofRectangle & ProjectorModel::getOutputSize() const {
    return m_output;
}


const unsigned int ProjectorModel::getBufferWidth() const {
    return m_buffer.getWidth();
}


const unsigned int ProjectorModel::getBufferHeight() const {
    return m_buffer.getHeight();
}


const ofRectangle & ProjectorModel::getBufferSize() const {
    return m_buffer;
}


void ProjectorModel::setSize(const unsigned int& output_width, const unsigned int& output_height, const unsigned int& buffer_width, const unsigned int& buffer_height) {
    m_output.set(0, 0, output_width, output_height);
    m_buffer.set(0, 0, buffer_width, buffer_height);
}

