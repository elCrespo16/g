#version 330 core
uniform mat4 modelViewProjectionMatrix;

layout (location = 0) in vec3 vertex;

void main()
{
	gl_Position    = modelViewProjectionMatrix * vec4(vertex,1.0);
}

