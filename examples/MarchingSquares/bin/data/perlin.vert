// Specifies the GLSL Version, in this case 1.5 for OpenGL 3.2
#version 150

// This is actually a value passed in from OF.
// You can tell that because it's got a "uniform" in front of it.
// This means that it's passed in for each vertex with exactly the same value.
uniform mat4 modelViewProjectionMatrix;
// This is called an attribute and every vertex has a different one.
// ... which means that the value passed in is different for each vertex
// because the each vertex has a slightly different position.
in vec4 position;

void main() {
    // gl_Position - This is what comes out of the vertex shader.
    // It's a variable with a fixed role: pass the position of the vertex to the triangle assembly.
    gl_Position = modelViewProjectionMatrix * position;
}