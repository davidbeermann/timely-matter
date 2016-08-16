#include "VectorFieldInputFactory.h"
#include "NoiseInputProvider.h"
#include "KinectInputProvider.h"


VectorFieldInputProvider* VectorFieldInputFactory::get(VectorFieldInputType type) {
    switch (type) {
        case VectorFieldInputType::NOISE:
            return new NoiseInputProvider();
            break;
        case VectorFieldInputType::KINECT:
            return new KinectInputProvider();
            break;
        default:
            return nullptr;
            break;
    }
}

