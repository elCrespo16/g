#version 330 core

uniform sampler2D colorMap;
in vec2 vtexCoord;

uniform float time;
const float pi = 3.141659;

in vec4 frontColor;
out vec4 fragColor;

vec3 red = vec3(1.,0.,0.);
vec3 yellow = vec3(1.,1.,0.);
vec3 green = vec3(0.,1.,0.);
vec3 cian = vec3(0.,1.,1.);
vec3 blue = vec3(0.,0.,1.);
vec3 magenta = vec3(1.,0.,1.);

void main()
{
	float r = texture(colorMap,vtexCoord).x;
	float func = sin(0.1*pi*2*time+2*pi*r);
	float y = (func + 1.0) * (7./2.);
	if(y < 0) fragColor = vec4(red,1.);
    else if(y<1) fragColor = vec4(mix(red,yellow,fract(y)),1.0);
    else if(y<2)fragColor = vec4(mix(yellow,green,fract(y)),1.0);
    else if(y<3)fragColor = vec4(mix(green,cian,fract(y)),1.0);
    else if(y<4)fragColor = vec4(mix(cian,blue,fract(y)),1.0);
    else if(y<6)fragColor = vec4(mix(blue,magenta,fract(y)),1.0);
    else if(y<7)fragColor = vec4(mix(magenta,red,fract(y)),1.0);
    else fragColor = vec4(red,1.);
}
