#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 147) out;

const float PI = 3.14159265359;
const float TWO_PI = PI * 2.0;

uniform mat4 modelViewProjectionMatrix;

uniform vec2 uTexSize;
uniform int uResolution;
uniform float uRadius;

out vec2 gTexCoord;


void main() {
    
    for (int i = 0; i < gl_in.length(); i++) {
        vec4 pos = gl_in[i].gl_Position;
        
        float increment = TWO_PI / uResolution;
        vec2 center = vec2(0.5f, 0.5f) * uTexSize;
        
        for (int j = 0; j < uResolution; j++) {
            gl_Position = pos;
            gTexCoord = center;
            EmitVertex();
            
            float angle = j * increment;
            float x = cos(angle) * uRadius;
            float y = sin(angle) * uRadius;
            vec4 offset = vec4(x, y, 0.f, 0.f);
            
            gl_Position = pos + modelViewProjectionMatrix * offset;
            gTexCoord = center + vec2(x, y);
            EmitVertex();
            
            float angle_next = (j+1) * increment;
            float x_next = cos(angle_next) * uRadius;
            float y_next = sin(angle_next) * uRadius;
            vec4 offset_next = vec4(x_next, y_next, 0.f, 0.f);
            
            gl_Position = pos + modelViewProjectionMatrix * offset_next;
            gTexCoord = center + vec2(x_next, y_next);
            EmitVertex();
        }
        
        EndPrimitive();
    }
    
}