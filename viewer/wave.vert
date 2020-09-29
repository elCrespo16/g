#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;
const float pi = 3.141592;
uniform float amp = 0.5;
uniform float freq = 0.25;

void main()
{
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0) * N.z;
    vtexCoord = texCoord;  
    float ang = amp * sin(freq *2*pi*time + vertex.y);
    mat4 rotx = mat4(vec4(1,0,0,0),vec4(0,cos(ang),sin(ang),0),vec4(0,-sin(ang),cos(ang),0),vec4(0,0,0,1));
    vec4 vertex2 = projectionMatrix* viewMatrix * rotx * modelMatrix * vec4(vertex,1.0);
    gl_Position = vertex2;
}
