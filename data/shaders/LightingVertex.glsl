#version 330 core

attribute vec3 a_position;
attribute vec3 a_normal;

varying vec3 v_normal;
varying vec3 v_fragPos;

uniform mat4 u_model;
uniform mat4 u_projView;

void main()
{
		
	v_fragPos = vec3(u_model * vec4(a_position, 1.0));
    v_normal = mat3(transpose(inverse(u_model))) * a_normal;

	gl_Position = u_projView * vec4(v_fragPos, 1.0);

}
