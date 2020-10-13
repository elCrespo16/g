#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
uniform float limit = 0.2;


void main()
{
	vec2 C = vec2(0.5, 0.5);
	float d = distance(vtexCoord, C);
	float smo = smoothstep(limit-0.07,limit+0.07,d);
	//if(smo == 1) fragColor = vec4(1.0);
	//else if(smo == 0) fragColor = vec4(1.,0.,0.,0.);
	fragColor = vec4(1.0) - vec4(0.,1-smo,1-smo,1-smo);

}
