#version 330 core

in vec3 c;
in vec2 uv;

void main(){
    vec3 col = mix(1.0 - c, c, smoothstep(0.3, 0.31, length(uv - .5)));

    gl_FragColor = vec4(col, 1.0);
}
