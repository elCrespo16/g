#version 330 core

in vec4 frontColor;
out vec4 fragColor;

in vec3 N;
in vec3 V;
in vec3 P;

uniform int n = 2;

uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

vec4 light(vec3 N, vec3 V, vec3 L, vec3 R) {
 /* Funcion original
  float NL=max(0, dot(N, L));
  float RV=max(0, dot(R, V));
  float ldiff=NL;
  float lspec=0; 
  if (NL>0) lspec=pow(RV, matShininess); 
  return matAmbient*lightAmbient + matDiffuse*lightDiffuse*ldiff + matSpecular*lightSpecular*lspec;
  */
  
  float NL=max(0, dot(N, L));
  float RV=max(0, dot(R, V));
  float ldiff=NL;
  float lspec=0; 
  if (NL>0) lspec=pow(RV, matShininess); 
  return matDiffuse*lightDiffuse*ldiff*(1./sqrt(n)) + matSpecular*lightSpecular*lspec;
}

vec3 lightPos(int i){
	vec3 initial = vec3(10,0,0);
	if (i == 0) return initial;
	else {
		float alpha = 360 / n;
		return vec3(cos(radians(alpha*i))*10, sin(radians(alpha*i))*10 ,0);
	}
}

vec3 Rlight(vec3 L) {
	return normalize(2*dot(N, L)*N-L);
}

void main()
{
	vec4 res = vec4(0.,0.,0.,0.);
	for(int i = 0;i < n;++i){
		vec3 L = normalize(lightPos(i) - P);
		vec3 R =  Rlight(L);
		res += light(N,V,L,R);
	}
    fragColor = res;
}
