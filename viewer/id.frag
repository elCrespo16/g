#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

uniform sampler2D colorMap;



void main()
{

	vec4 blue = vec4(0.,0.,1.0,0.);
	vec4 jejexd;
	
	if (fract(vtexCoord.s) < 1./6.){
		jejexd = texture(colorMap,vec2(0.83/10.+fract(vtexCoord.s)*6/10.,vtexCoord.t));
		if(jejexd.a < 0.5) discard;
		else fragColor = jejexd;
		}
	else if (fract(vtexCoord.s) < 2./6.) {
		jejexd = texture(colorMap,vec2(-0.08/10+(fract(vtexCoord.s)-1./6.)*6/10.,vtexCoord.t));
		if(jejexd.a < 0.5) discard;
		else fragColor = jejexd;
	}
	else if (fract(vtexCoord.s) < 3./6.) {
		jejexd = texture(colorMap,vec2(5.8/10.+(fract(vtexCoord.s)-2./6.)*6/10.,vtexCoord.t));
		if(jejexd.a < 0.5) discard;
		else fragColor = jejexd;
		}
	else if (fract(vtexCoord.s) < 4./6.){
		jejexd =  texture(colorMap,vec2(3.85/10.+(fract(vtexCoord.s)-3./6.)*6/10.,vtexCoord.t));
		if(jejexd.a < 0.5) discard;
		else fragColor = jejexd;
	}
	else if (fract(vtexCoord.s) < 5./6.) {
		jejexd = texture(colorMap,vec2(7.8/10.+(fract(vtexCoord.s)-4./6.)*6/10.,vtexCoord.t));
		if(jejexd.a < 0.5) discard;
		else fragColor = jejexd;
	}
	else {
		jejexd =  texture(colorMap,vec2(5.83/10.+(fract(vtexCoord.s)-5./6.)*6/10.,vtexCoord.t));
		if(jejexd.a < 0.5) discard;
		else fragColor = jejexd;
		}
	//if (fract(vtexCoord.s) < 1./6.) fragColor = vec4(0.,0.,1.0,0.);
	//else fragColor = texture(colorMap,vtexCoord);
    
}
