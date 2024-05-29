#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

out vec3 i_normal;
out vec2 i_uv;

uniform mat4 u_mvp;
uniform mat4 u_vp;

uniform float u_baseScale;
uniform float u_resolution;

layout(binding = 2, std430) buffer ssbo1 {
	vec4 _Position[];
};

void main(){
	i_normal = normal;
	i_uv = texCoord;

	float s = u_baseScale * 0.5 / u_resolution;
	mat4 scale = mat4(
		s, 0.0, 0.0, 0.0,
		0.0, s, 0.0, 0.0,
		0.0, 0.0, s, 0.0,
		0.0, 0.0, 0.0, 1.0
	);

	vec4 p = _Position[gl_InstanceID];
	p.z += 2.0;

	mat4 translation = mat4(
		1.0, 0.0, 0.0, 0.0,
		0.0, 1.0, 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		p.x, p.y, p.z, 1.0
	);
	mat4 m = u_vp * translation * scale;
	gl_Position =  m * position;
}
