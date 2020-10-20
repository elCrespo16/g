#version 330 core

in vec4 frontColor;
in  vec2 vtexCoord;
out vec4 fragColor;

uniform int bandera = 3;

void main()
{
	vec4 green = vec4(0.,1.,0.,0.);
	vec4 yellow = vec4(1.,1.,0.,0.);
	vec4 blue = vec4(0.,0.,1.,0.);
	vec4 red = vec4(1.,0.,0.,0.);
	if(bandera == 1){
		if(fract(vtexCoord.t) < 1./3.) fragColor = blue;
		else if(fract(vtexCoord.t) < 2./3.) fragColor = yellow;
		else fragColor = green;
	}
	else if(bandera == 2){
		if(fract(vtexCoord.s) < 1./3.) fragColor = red;
		else if(fract(vtexCoord.s) < 2./3.){
			if(distance(vec2(vtexCoord.s,(vtexCoord.t+0.15)/1.3333),vec2(0.5,0.5)) < 0.15) fragColor = green;
		 	else fragColor = blue;
		 }
		else fragColor = yellow;
	}
	else {
		if(fract(vtexCoord.s) < 1./2.){
		 	if(distance(vec2(vtexCoord.s,(vtexCoord.t+0.15)/1.3333),vec2(1./4.,0.5)) < 0.15) discard;
		 }
		else {
			if(distance(vec2(vtexCoord.s,(vtexCoord.t+0.15)/1.3333),vec2(3./4.,0.5)) < 0.2 && distance(vec2(vtexCoord.s,(vtexCoord.t+0.15)/1.3333),vec2(2.5/4.,0.5)) > 0.2) discard;
		}
		fragColor = green;
	}
}
