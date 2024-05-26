#version 100

precision mediump float;

varying vec2 fragTexCoord;

uniform sampler2D previous_texture;
uniform vec2 screen_resolution;

void main() {
    vec2 coords = fragTexCoord;
    float center = texture2D(previous_texture, coords).r;

    float num = 0.0;
    for (float i = -1.0; i <= 1.0; i++) {
        for (float j = -1.0; j <= 1.0; j++) {
            if (i == 0.0 && j == 0.0) continue; // Skip the center cell

            float x = coords.x + i * 1.0/screen_resolution.x;
            float y = coords.y + j * 1.0/screen_resolution.y;

            num += texture2D(previous_texture, vec2(x, y)).r;
        }
    }

float a = 0.0;
if (center > 0.5) {
    if(num > 1.5 && num < 3.5){
        a = 1.0;
    }else{
       a = 0.0;
    }
} else {
    if (num > 2.5 && num < 3.5) {
        a = 1.0;
    } else {
        a = 0.0;
    }
}

    gl_FragColor = vec4(a, a, a, 255);
}