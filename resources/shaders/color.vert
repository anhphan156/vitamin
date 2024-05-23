#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 texCoord;

out vec3 c;
out vec2 uv;
uniform mat4 u_mvp;

void main(){
    c = color;
    uv = texCoord;

    gl_Position = u_mvp * position;
}
