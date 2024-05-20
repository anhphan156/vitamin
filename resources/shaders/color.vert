#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 c;
out vec2 uv;
uniform mat2 u_r;

void main(){
    c = color;
    uv = texCoord;

    vec2 p = u_r * position.xy;
    gl_Position = vec4(p, 0.0, 1.0);
}
