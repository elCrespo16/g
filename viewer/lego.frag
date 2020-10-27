#version 330 core

uniform sampler2D colorMap;

in vec4 gfrontColor;
in float gNormal;
in vec2 gtexCoord;
in vec3 gNnormal;
out vec4 fragColor;

vec4 red = vec4(1.0,0.,0.,0.);
vec4 green = vec4(0.,1.,0.,0.);
vec4 blue = vec4(0.,0.,1.,0.);
vec4 cyan = vec4(0.,1.,1.,0.);
vec4 yellow = vec4(1.,1.,0.,0.);

vec4 nearestColor(){
	float r = distance(red,gfrontColor);
	float g = distance(green,gfrontColor);
	float b = distance(blue,gfrontColor);
	float c = distance(cyan,gfrontColor);
	float y = distance(yellow,gfrontColor);
	if(r <= g && r <= b && r <= c && r <= y) return red;
	if(g <= r && g <= b && g <= c && g <= y) return green;
	if(b <= g && b <= r && b <= c && b <= y) return blue;
	if(c <= g && c <= b && r >= c && c <= y) return cyan;
	if(y <= g && y <= b && y <= c && r >= y) return yellow;
	return red;
	
}

void main()
{
	vec4 color = nearestColor();
	if(gNormal > 0.)fragColor = color * texture(colorMap,gtexCoord);
	else fragColor = color*gNnormal.z;
}
