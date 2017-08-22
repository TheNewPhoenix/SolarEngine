#version 330 core

in vec3 aPos;
in vec4 aColor;
in vec2 aTexCoord;

uniform mat4 projView;
uniform mat4 model;

out vec4 fragColor;
out vec2 texCoord;

void main()
{
	gl_Position =  projView * model * vec4(aPos,1);
	fragColor = aColor;
	texCoord = aTexCoord;
}