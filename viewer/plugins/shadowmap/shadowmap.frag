#version 330 core

out vec4 fragColor;

uniform mat4 modelViewMatrix;
uniform sampler2D shadowMap;
uniform vec3 lightPos;  
in vec3 N; 
in vec3 P;
in vec4 vtexCoord;



void main()
{
    vec3 L =  normalize((modelViewMatrix*vec4(lightPos,1.0)).xyz-P);
    float NdotL = max(0.0, dot(normalize(N),L));   

    vec4 color = vec4(NdotL);

    vec2 st = vtexCoord.st / vtexCoord.q;

	float storedDepth = texture(shadowMap, st).r;
	float trueDepth = vtexCoord.p / vtexCoord.q;

	if (trueDepth <= storedDepth)
		fragColor = color;
	else
		fragColor = 0.2*color;

    if (false) // debug, show texture
    {
        color = texture(shadowMap, (1./512.)*gl_FragCoord.xy);
        color.r = 1.0;
        fragColor = color;
    }
    
}

