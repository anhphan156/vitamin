#version 330 core

in vec3 c;

void main(){

    gl_FragColor = vec4(c, 1.0);
}
