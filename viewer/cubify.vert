#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

vec3 center () {
	return (boundingBoxMax + boundingBoxMin) / 2;
}

vec4 divideByGreatest (vec3 V) {
	float X = abs(V.x);
	float Y = abs(V.y);
	float Z = abs(V.z);
	if(X >= Y && X >= Z) return vec4(V.x/X,V.y/X,V.z/X,1.);
	if(Y >= X && Y >= Z) return vec4(V.x/Y,V.y/Y,V.z/Y,1.);
	return vec4(V.x/Z,V.y/Z,V.z/Z,1.);
}

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    vec3 cent = center();
    vec3 newVec = vertex;
    gl_Position = projectionMatrix * viewMatrix* modelMatrix * divideByGreatest(vertex);
}
