#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 i_normal;
out vec2 i_uv;
uniform mat4 u_mvp;

void main(){
    i_normal = normal;
    i_uv = texCoord;

    gl_Position = u_mvp * position;
}
