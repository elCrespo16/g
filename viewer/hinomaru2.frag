#version 330 core

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform bool classic;

void main()
{
	vec2 C = vec2(0.5, 0.5);
	float d = distance(vtexCoord, C);
    if(classic){
		if(d < 0.2) fragColor = vec4(1.,0.,0.,0.);
    	else fragColor = vec4(1.0);
    }
    else {
    	float p = 3.1416/16;
    	vec2 u = vec2(vtexCoord.s,vtexCoord.t) - C;
    	if(d < 0.2) fragColor = vec4(1.,0.,0.,0.);
    	else if(mod(atan(u.t,u.s)/p+0.5,2) < 1)fragColor = vec4(1.,0.,0.,0.);
    	else fragColor = vec4(1.0);	
    }
}
