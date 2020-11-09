#version 330 core

uniform sampler2D colorMap;

in vec4 frontColor;
out vec4 fragColor;
in vec2 vtexCoord;
in vec3 N;

vec2 leftEye = vec2(0.34,0.65);

vec2 rightEye = vec2(0.66,0.65);

void main()
{
	vec2 TleftEye = vec2(0.44,0.65);

	vec2 TrightEye = vec2(0.56,0.65);
	if(distance(vtexCoord,leftEye-0.1*N.xy) <= 0.05 ||  distance(vtexCoord,rightEye-0.1*N.xy) <= 0.05) fragColor = vec4(0.);
    else if(distance(vtexCoord,TleftEye) <= 0.15 ||  distance(vtexCoord,TrightEye) <= 0.15)fragColor = texture(colorMap,vec2(0.5,0.5));
    
    else fragColor = texture(colorMap,vtexCoord);
    //fragColor = texture(colorMap,vtexCoord);
}
