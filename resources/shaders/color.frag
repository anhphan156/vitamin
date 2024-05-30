#version 330 core

in vec3 i_normal;
in vec2 i_uv;
in vec3 i_fragPos;
in vec3 i_lightPos;

void main(){
		vec3 lightDir = normalize(i_lightPos - i_fragPos);

		float l = max(0.0, dot(lightDir, i_normal));

		vec3 col = vec3(l);

    gl_FragColor = vec4(col, 1.0);
}
