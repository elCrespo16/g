#version 330 core

in vec4 frontColor;
in vec3 vPos;
out vec4 fragColor;

uniform mat3 normalMatrix;

void main()
{
	vec3 vxPos = dFdx(vPos);
	vec3 vyPos = dFdy(vPos);
	vec3 c = normalize(normalMatrix * cross(vxPos,vyPos));
    fragColor = frontColor * c.z;
}
