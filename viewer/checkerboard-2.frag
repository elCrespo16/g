#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform float n = 8;

void main()
{
	float t = mod(vtexCoord.t*n,2.);
	if(mod(vtexCoord.s*n,2.) < 1){
		if(t < 1)fragColor = vec4 (0.8);
		else fragColor = vec4 (0.0);
	}
	else{
	 if(!(t < 1))fragColor = vec4 (0.8);
	 else fragColor = vec4 (0.0);
	}
}
