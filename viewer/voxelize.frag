#version 330 core

uniform sampler2D colorMap;

in vec4 gfrontColor;
in float gNormal;
in vec2 gtexCoord;
out vec4 fragColor;

void main()
{
	fragColor = gfrontColor;
}
