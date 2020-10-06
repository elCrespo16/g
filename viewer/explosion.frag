#version 330 core

uniform sampler2D colorMap;

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;

uniform float time;

vec2 calcTextCoord(int frame){
	vec2 result;
	result.s = (frame % 8 + vtexCoord.s)/8.;
	result.t = (5. - (frame / 8) + vtexCoord.t)/6. ;
	return result;
}

void main()
{
	float slice = 1.0/60.;
	int frame = int(mod(time / slice,48));
	vec4 tcolor = texture(colorMap,calcTextCoord(frame));
    fragColor = tcolor * tcolor.a ;
    //fragColor = texture(colorMap,vec2(vtexCoord.s*(1./8.) + 7./8.,vtexCoord.t*(1./6.)));
}
