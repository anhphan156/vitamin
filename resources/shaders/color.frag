#version 330 core

in vec3 i_normal;
in vec2 i_uv;

void main(){
		vec3 col = i_normal * .5 + .5;

    gl_FragColor = vec4(col, 1.0);
}
