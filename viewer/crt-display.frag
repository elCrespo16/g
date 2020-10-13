#version 330 core

in vec4 frontColor;
out vec4 fragColor;

uniform int n = 2;

void main()
{
	int i = int(floor(gl_FragCoord.y));
	if(i % n == 0.0) fragColor = frontColor;
	//else fragColor = vec4(0.);
    else discard;
}
