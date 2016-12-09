#version 330

// create constant arrays of kernel values
// https://www.opengl.org/discussion_boards/showthread.php/170193-Constant-vec3-array-no-go
// kernel values calculated with Gaussian Kernel Calculator - Sigma 2.0:
// http://dev.theomader.com/gaussian-kernel-calculator/
const float KERNEL_3[3] = float[](0.319466, 0.361069, 0.319466);
const float KERNEL_5[5] = float[](0.153388, 0.221461, 0.250301, 0.221461, 0.153388);
const float KERNEL_7[7] = float[](0.071303, 0.131514, 0.189879, 0.214607, 0.189879, 0.131514, 0.071303);
const float KERNEL_9[9] = float[](0.028532, 0.067234, 0.124009, 0.179044, 0.20236, 0.179044, 0.124009, 0.067234, 0.028532);
const float KERNEL_11[11] = float[](0.0093, 0.028002, 0.065984, 0.121703, 0.175713, 0.198596, 0.175713, 0.121703, 0.065984, 0.028002, 0.0093);
const float KERNEL_13[13] = float[](0.002406, 0.009255, 0.027867, 0.065666, 0.121117, 0.174868, 0.197641, 0.174868, 0.121117, 0.065666, 0.027867, 0.009255, 0.002406);
const float KERNEL_15[15] = float[](0.000489, 0.002403, 0.009246, 0.02784, 0.065602, 0.120999, 0.174697, 0.197448, 0.174697, 0.120999, 0.065602, 0.02784, 0.009246, 0.002403, 0.000489);

int strength;

uniform sampler2DRect tex0;
uniform int uStrength;
uniform bool uVertical;

in vec2 vTexCoord;

out vec4 fragColor;


void main() {
    
    if (uStrength < 0) strength = 0;
    else if (uStrength > 7) strength = 7;
    else strength = uStrength;
    
    int kernel_size = strength * 2 + 1;
    vec4 color;
    
    if (kernel_size == 1) {
        color = texture(tex0, vTexCoord);
    } else {
        color = vec4(0.0);
        switch (kernel_size) {
            case 3:
                color += KERNEL_3[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_3[1] * texture(tex0, vTexCoord);
                color += KERNEL_3[2] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                break;
            case 5:
                color += KERNEL_5[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -2.0, uVertical ? -2.0 : 0.0));
                color += KERNEL_5[1] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_5[2] * texture(tex0, vTexCoord);
                color += KERNEL_5[3] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                color += KERNEL_5[4] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 2.0, uVertical ? 2.0 : 0.0));
                break;
            case 7:
                color += KERNEL_7[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -3.0, uVertical ? -3.0 : 0.0));
                color += KERNEL_7[1] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -2.0, uVertical ? -2.0 : 0.0));
                color += KERNEL_7[2] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_7[3] * texture(tex0, vTexCoord);
                color += KERNEL_7[4] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                color += KERNEL_7[5] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 2.0, uVertical ? 2.0 : 0.0));
                color += KERNEL_7[6] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 3.0, uVertical ? 3.0 : 0.0));
                break;
            case 9:
                color += KERNEL_9[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -4.0, uVertical ? -4.0 : 0.0));
                color += KERNEL_9[1] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -3.0, uVertical ? -3.0 : 0.0));
                color += KERNEL_9[2] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -2.0, uVertical ? -2.0 : 0.0));
                color += KERNEL_9[3] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_9[4] * texture(tex0, vTexCoord);
                color += KERNEL_9[5] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                color += KERNEL_9[6] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 2.0, uVertical ? 2.0 : 0.0));
                color += KERNEL_9[7] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 3.0, uVertical ? 3.0 : 0.0));
                color += KERNEL_9[8] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 4.0, uVertical ? 4.0 : 0.0));
                break;
            case 11:
                color += KERNEL_11[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -5.0, uVertical ? -5.0 : 0.0));
                color += KERNEL_11[1] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -4.0, uVertical ? -4.0 : 0.0));
                color += KERNEL_11[2] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -3.0, uVertical ? -3.0 : 0.0));
                color += KERNEL_11[3] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -2.0, uVertical ? -2.0 : 0.0));
                color += KERNEL_11[4] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_11[5] * texture(tex0, vTexCoord);
                color += KERNEL_11[6] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                color += KERNEL_11[7] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 2.0, uVertical ? 2.0 : 0.0));
                color += KERNEL_11[8] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 3.0, uVertical ? 3.0 : 0.0));
                color += KERNEL_11[9] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 4.0, uVertical ? 4.0 : 0.0));
                color += KERNEL_11[10] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 5.0, uVertical ? 5.0 : 0.0));
                break;
            case 13:
                color += KERNEL_13[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -6.0, uVertical ? -6.0 : 0.0));
                color += KERNEL_13[1] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -5.0, uVertical ? -5.0 : 0.0));
                color += KERNEL_13[2] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -4.0, uVertical ? -4.0 : 0.0));
                color += KERNEL_13[3] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -3.0, uVertical ? -3.0 : 0.0));
                color += KERNEL_13[4] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -2.0, uVertical ? -2.0 : 0.0));
                color += KERNEL_13[5] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_13[6] * texture(tex0, vTexCoord);
                color += KERNEL_13[7] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                color += KERNEL_13[8] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 2.0, uVertical ? 2.0 : 0.0));
                color += KERNEL_13[9] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 3.0, uVertical ? 3.0 : 0.0));
                color += KERNEL_13[10] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 4.0, uVertical ? 4.0 : 0.0));
                color += KERNEL_13[11] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 5.0, uVertical ? 5.0 : 0.0));
                color += KERNEL_13[12] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 6.0, uVertical ? 6.0 : 0.0));
                break;
            case 15:
                color += KERNEL_15[0] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -7.0, uVertical ? -7.0 : 0.0));
                color += KERNEL_15[1] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -6.0, uVertical ? -6.0 : 0.0));
                color += KERNEL_15[2] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -5.0, uVertical ? -5.0 : 0.0));
                color += KERNEL_15[3] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -4.0, uVertical ? -4.0 : 0.0));
                color += KERNEL_15[4] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -3.0, uVertical ? -3.0 : 0.0));
                color += KERNEL_15[5] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -2.0, uVertical ? -2.0 : 0.0));
                color += KERNEL_15[6] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : -1.0, uVertical ? -1.0 : 0.0));
                color += KERNEL_15[7] * texture(tex0, vTexCoord);
                color += KERNEL_15[8] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 1.0, uVertical ? 1.0 : 0.0));
                color += KERNEL_15[9] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 2.0, uVertical ? 2.0 : 0.0));
                color += KERNEL_15[10] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 3.0, uVertical ? 3.0 : 0.0));
                color += KERNEL_15[11] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 4.0, uVertical ? 4.0 : 0.0));
                color += KERNEL_15[12] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 5.0, uVertical ? 5.0 : 0.0));
                color += KERNEL_15[13] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 6.0, uVertical ? 6.0 : 0.0));
                color += KERNEL_15[14] * texture(tex0, vTexCoord + vec2(uVertical ? 0.0 : 7.0, uVertical ? 7.0 : 0.0));
                break;
            default:
                break;
        }
    }
    
    fragColor = color;
    
}

