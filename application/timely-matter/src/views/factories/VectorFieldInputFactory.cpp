#include "VectorFieldInputFactory.hpp"
#include "NoiseInput.hpp"
#include "KinectInput.hpp"

using namespace timelymatter;


VectorFieldInput& VectorFieldInputFactory::get(const AppMode mode) {
    VectorFieldInput* input;
    
    switch (mode) {
        case AppMode::NOISE:
            input = new NoiseInput();
            break;
        case AppMode::KINECT:
            input = new KinectInput();
            break;
        default:
            ofLog() << "Invalid mode. Creating default input.";
            input = new NoiseInput();
            break;
    }
    
    return *input;
}

