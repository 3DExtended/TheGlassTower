#version 330 core

in vec2 texCoord;

out vec4 outColor;

uniform sampler2D baseTex;

void main()
{
	outColor = vec4(texture(baseTex, texCoord).rgb, 1.0);
}