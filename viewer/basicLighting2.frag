#version 330 core

in vec4 frontColor;
in vec3 n;
out vec4 fragColor;

void main()
{
	vec3 N = normalize(n);
    fragColor = frontColor * N.z;
}
