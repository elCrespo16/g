#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;
uniform float time;

void main()
{
     
    vec4 M = modelMatrix * vec4(vertex,1.0);
    float ang = (M.y - 0.5) * sin(time);
    vec3 N = normalize(normalMatrix * normal);
    frontColor = vec4(color,1.0);
    vtexCoord = texCoord;
    if(M.y >= 0.5){
	M -= vec4(0,1,0,0);
	M = mat4(vec4(1,0,0,0),vec4(0,cos(ang),sin(ang),0),vec4(0,-sin(ang),cos(ang),0),vec4(0,0,0,1)) * M;
	M += vec4(0,1,0,0);
    }
    gl_Position = projectionMatrix * viewMatrix * M;
}
