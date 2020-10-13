#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

void main()
{
	vec2 C = vec2(0.5, 0.5);
	float d = distance(vtexCoord, C);
	if(d < 0.2) fragColor = vec4(1.,0.,0.,0.);
    else fragColor = vec4(1.0);
}
