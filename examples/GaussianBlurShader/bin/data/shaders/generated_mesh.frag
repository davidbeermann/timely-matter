#version 330 core

uniform sampler2DRect tex0;

in vec2 gTexCoord;

out vec4 fragColor;


void main() {
    
//    fragColor = vec4(1.f, 1.f, 1.f, 1.f);
    fragColor = texture(tex0, gTexCoord);
    
}