#include "ProjectorModel.hpp"

#define DEFAULT_WIDTH 1024
#define DEFAULT_HEIGHT 768

using namespace timelymatter;


ProjectorModel::ProjectorModel() {
    // set default values
    m_size.set(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);
}


ProjectorModel& ProjectorModel::get() {
    static ProjectorModel model;
    return model;
}


const unsigned int ProjectorModel::getWidth() const {
    return m_size.getWidth();
}


const unsigned int ProjectorModel::getHeight() const {
    return m_size.getHeight();
}


const ofRectangle ProjectorModel::getSize() const {
    return m_size;
}

