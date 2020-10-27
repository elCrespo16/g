#version 330 core

uniform sampler2D colorMap;

in vec4 gfrontColor;
in float gNormal;
in vec2 gtexCoord;
out vec4 fragColor;

void main()
{
	if(gNormal == 1.0) fragColor = vec4(step(0.5,gfrontColor.x),step(0.5,gfrontColor.y),step(0.5,gfrontColor.z),1.0)*texture(colorMap,gtexCoord);
    else fragColor = vec4(step(0.5,gfrontColor.x),step(0.5,gfrontColor.y),step(0.5,gfrontColor.z),1.0);
}
