#version 330 core

in vec4 fragColor;
in vec2 texCoord;

out vec4 color;

uniform sampler2D ourTexture;

void main(){
  color = fragColor;
}