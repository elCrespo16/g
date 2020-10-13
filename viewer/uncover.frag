#version 330 core

in vec4 frontColor;
in float ndc;
out vec4 fragColor;

uniform float time;

void main()
{
	if(ndc < time-1) fragColor = vec4(0.,0.,1.0,0.);
	else discard; 
	//fragColor = frontColor;
}
