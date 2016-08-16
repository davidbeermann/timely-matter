#pragma once

#include "ofMain.h"
#include "VectorFieldInputType.h"
#include "VectorFieldInputProvider.h"


class VectorFieldInputFactory {
public:
    // You cannot create an object of an abstract class type;
    // however, you can use pointers and references to abstract class types.
    // https://msdn.microsoft.com/en-us/library/c8whxhf1.aspx
    VectorFieldInputProvider* get(VectorFieldInputType type);
};