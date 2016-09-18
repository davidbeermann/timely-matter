#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 150) out;

const float PI = 3.14159265359;
const float TWO_PI = PI * 2.0;

uniform mat4 modelViewProjectionMatrix;

uniform int segments;
uniform int radius;
uniform int amplitude;
uniform float speed;

out vec4 fColor;

// color conversion from HSV to RGB
// http://stackoverflow.com/questions/15095909/from-rgb-to-hsv-in-opengl-glsl
// http://lolengine.net/blog/2013/07/27/rgb-to-hsv-in-glsl
vec3 hsv2rgb(vec3 c)
{
    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);
    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);
    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);
}


void main (void) {
    
    float start_angle = speed * TWO_PI;
    float inc = TWO_PI / segments;
    float inc_z = TWO_PI * 3 / segments;
    
    for (int i = 0; i < gl_in.length(); i++) {
        vec4 pos = gl_in[i].gl_Position;
        
        for (int j = 0; j < segments; j++) {
            
            gl_Position = pos;
            fColor = vec4(1.f, 1.f, 1.f, 1.f);
            EmitVertex();
            
            float angle = j * inc;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            float z = sin(start_angle + j * inc_z) * amplitude;
            
            gl_Position = pos + modelViewProjectionMatrix * vec4(x, y, z, 0.0);
            fColor = vec4(hsv2rgb(vec3(angle/TWO_PI, 1.f, 1.f)), 1.f);
            EmitVertex();
            
            float angle_next = (j + 1) * inc;
            float x_next = cos(angle_next) * radius;
            float y_next = sin(angle_next) * radius;
            float z_next = sin(start_angle + (j + 1) * inc_z) * amplitude;
            
            gl_Position = pos + modelViewProjectionMatrix * vec4(x_next, y_next, z_next, 0.0);
            fColor = vec4(hsv2rgb(vec3(angle_next/TWO_PI, 1.f, 1.f)), 1.f);
            EmitVertex();
        }
        
        EndPrimitive();
    }
    
}