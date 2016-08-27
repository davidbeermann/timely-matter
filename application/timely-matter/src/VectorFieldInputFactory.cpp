#include "VectorFieldInputFactory.h"
#include "NoiseInputProvider.h"
#include "KinectInputProvider.h"


VectorFieldInputProvider* VectorFieldInputFactory::get(const AppMode mode) {
    switch (mode) {
        case AppMode::NOISE:
            return new NoiseInputProvider();
            break;
        case AppMode::KINECT:
            return new KinectInputProvider();
            break;
        default:
            return nullptr;
            break;
    }
}

