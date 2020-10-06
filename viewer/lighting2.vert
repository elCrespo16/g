#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelViewMatrix;
uniform mat3 normalMatrix;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

//No funciona, cuando haya que hacer los calculos de iluminacion, se hacen con vec3 y por ultimo se pasa a vec4 si no da errores en la parte especular
/*vec4 light(vec4 N, vec4 V, vec4 L, vec4 R){
	float LS = 0.0;
	float NL = max(0.,dot(N.xyz, L.xyz));
	if (NL > 0.) LS = pow(max(0.0, dot(R.xyz, V.xyz)),matShininess);
	return matAmbient * lightAmbient + matDiffuse * lightDiffuse * NL + matSpecular * lightSpecular * LS;
}

void main()
{
	vec4 P = modelViewMatrix * vec4(vertex, 1.);
    vec4 N = vec4(normalize(normalMatrix * normal),1.0);
	vec4 L = normalize(lightPosition - P);
	vec4 V = (-normalize(P));
	vec4 R = normalize(2 * dot(N,L) * N - L);
	gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);
    frontColor = light(N,V,L,R);
    vtexCoord = texCoord;
    
}*/

vec4 light2(vec3 N, vec3 V, vec3 L, vec3 R) {
  float NL=max(0, dot(N, L));
  float RV=max(0, dot(R, V));
  float ldiff=NL;
  float lspec=0; 
  if (NL>0) lspec=pow(RV, matShininess); 
  return matAmbient*lightAmbient + matDiffuse*lightDiffuse*ldiff + matSpecular*lightSpecular*lspec;
}

void main() { 
  vec3 P=(modelViewMatrix * vec4(vertex.xyz, 1)).xyz;
  vec3 N=normalize(normalMatrix*normal);
  vec3 V=normalize(-P);
  vec3 L=normalize(lightPosition.xyz-P);
  vec3 R = normalize(2*dot(N, L)*N-L);
  frontColor=light2(N, V, L, R);
  gl_Position = modelViewProjectionMatrix*vec4(vertex.xyz, 1.0);
}
