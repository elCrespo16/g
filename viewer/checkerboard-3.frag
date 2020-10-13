#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
	/*
	float slice = 1/n;
	float sizet = vtexCoord.t - floor(vtexCoord.t/slice) * slice;
	float sizes = vtexCoord.s - floor(vtexCoord.s/slice) * slice;
	if(sizet <= slice/9 || sizes <= slice/9) fragColor = vec4 (0.0);
	else fragColor = vec4 (0.8);
	*/
	float x = fract(vtexCoord.x*n);
	float y = fract(vtexCoord.y*n);
	if(x>0.1 && y>0.1)fragColor = vec4 (0.8);
	else fragColor = vec4 (0.0);
} 
