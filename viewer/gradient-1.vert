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

void main()
{
    float dist = boundingBoxMax.y-boundingBoxMin.y;
    vec3 N = normalize(normalMatrix * normal);
    vtexCoord = texCoord;
    vec4 M = modelMatrix * vec4(vertex,1.0);
    if(M.y-boundingBoxMin.y<= dist/4) frontColor = vec4(mix(vec3(1,0,0),vec3(1,1,0),(M.y-(boundingBoxMin.y))/(dist/4)),1.0);
    else if(M.y-boundingBoxMin.y<= dist*2/4)frontColor = vec4(mix(vec3(1,1,0),vec3(0,1,0),(M.y-(boundingBoxMin.y+dist/4))/(dist/4)),1.0);
    else if(M.y-boundingBoxMin.y<= dist*3/4)frontColor = vec4(mix(vec3(0,1,0),vec3(0,1,1),(M.y-(boundingBoxMin.y+dist*2/4))/(dist/4)),1.0);
    else frontColor = vec4(mix(vec3(0,1,1),vec3(0,0,1),(M.y-(boundingBoxMin.y+dist*3/4))/(dist/4)),1.0);
    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
}
