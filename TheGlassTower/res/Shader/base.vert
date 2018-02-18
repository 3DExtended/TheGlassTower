#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;

out vec2 texCoord;

uniform mat4 matTrans;

void main()
{
	texCoord = texture;

	// Window Position
	gl_Position = matTrans * vec4(vertex, 1.0);
}