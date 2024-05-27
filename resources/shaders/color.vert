#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 i_normal;
out vec2 i_uv;

uniform mat4 u_mvp;
uniform mat4 u_vp;

layout(binding = 2, std430) buffer ssbo1 {
	mat4 modelMatrices[];
};

void main(){
    i_normal = normal;
    i_uv = texCoord;

    gl_Position = u_vp * modelMatrices[gl_InstanceID] * position;
    //gl_Position = u_mvp * position;
}
