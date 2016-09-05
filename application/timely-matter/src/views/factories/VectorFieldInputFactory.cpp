#include "VectorFieldInputFactory.hpp"
#include "NoiseInput.hpp"
#include "KinectInput.hpp"

using namespace timelymatter;


VectorFieldInput VectorFieldInputFactory::get(const AppMode mode) {
    switch (mode) {
        case AppMode::NOISE:
            return NoiseInput();
            break;
        case AppMode::KINECT:
            return KinectInput();
            break;
        default:
            ofLog() << "Invalid mode. Creating default input.";
            return NoiseInput();
            break;
    }
}

