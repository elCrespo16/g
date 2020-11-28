#version 330 core

layout (location = 0) in vec3 vertex;

out vec4 frontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;

void main()
{
	float scaleX = boundingBoxMax.x - boundingBoxMin.x, scaleY = boundingBoxMax.y - boundingBoxMin.y, scaleZ= boundingBoxMax.z - boundingBoxMin.z;
    frontColor = vec4(0.,0.,0.,1.);
    vec3 vertex2 = vec3(vertex.x*scaleX,vertex.y*scaleY,vertex.z*scaleZ);
    vec3 center = (boundingBoxMax-boundingBoxMin)/2;
    gl_Position = modelViewProjectionMatrix * vec4(vertex2-center, 1.0);
}
