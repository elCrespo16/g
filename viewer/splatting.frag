#version 330 core

uniform sampler2D noise0;
uniform sampler2D rock1;
uniform sampler2D grass2;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
    fragColor = mix(texture(rock1,vtexCoord),texture(grass2,vtexCoord),texture(noise0,vtexCoord).r);
}
