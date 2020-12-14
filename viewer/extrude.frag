#version 330 core

out vec4 fragColor;
in vec3 gnormal;

uniform mat3 normalMatrix;

void main()
{
    fragColor = vec4((normalMatrix*gnormal).z);
}
