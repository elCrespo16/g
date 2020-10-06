#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;

uniform vec2 Min=vec2(-1,-1);
uniform vec2 Max=vec2(1,1);

uniform mat4 modelViewProjectionMatrix;
uniform mat3 normalMatrix;

void main()
{
    frontColor = vec4(color,1.0);
    float x = 2.0*(texCoord.x-Min.x)/(Max.x-Min.x);
    float y = 2.0*(texCoord.y-Min.y)/(Max.y-Min.y);
    gl_Position = vec4(x-1.0,y-1.0,0, 1.0);
}
