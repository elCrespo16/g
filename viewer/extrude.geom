#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec3 vnormal[];
out vec3 gnormal;

uniform float d = 0.5;
uniform mat4 modelViewProjectionMatrix;

void pVertex(vec4 V, vec3 N){
	gl_Position = modelViewProjectionMatrix * V;
	gnormal = N;
	EmitVertex();
}


void main( void )
{
	vec3 norm = vec3(0,0,0);
	for( int i = 0 ; i < 3 ; i++ )
	{
		norm += vnormal[i];
	}
	norm = normalize(norm) ;
    vec4 v1 = gl_in[0].gl_Position, v2 = gl_in[1].gl_Position, v3 = gl_in[2].gl_Position;
    vec4 v1p = gl_in[0].gl_Position, v2p = gl_in[1].gl_Position, v3p = gl_in[2].gl_Position;
    v1p += d*vec4(norm,0.);
    v2p += d*vec4(norm,0.);
    v3p += d*vec4(norm,0.);
    vec3 n1 = -norm, n2 = norm, n3 = cross(v1.xyz-v1p.xyz,v2.xyz-v1p.xyz), n4 = -cross(v1.xyz-v1p.xyz,v3.xyz-v1p.xyz), n5 = cross(v2.xyz-v2p.xyz,v3.xyz-v2p.xyz);
    n3 = normalize(n3);
    n4 = normalize(n4);
    n5 = normalize(n5);
    //Triangulo original
    pVertex(v1,n1);
    pVertex(v2,n1);
    pVertex(v3,n1);
	EndPrimitive();
   
   	//Triangulo arriba
   	pVertex(v1p,n2);
    pVertex(v2p,n2);
    pVertex(v3p,n2);
	EndPrimitive();
	
	//Triangulo derecha 1
	pVertex(v1,n3);
    pVertex(v1p,n3);
    pVertex(v2,n3);
    pVertex(v2p,n3);
	EndPrimitive();
	
	
	//Triangulo izquierda 1
	pVertex(v1,n4);
    pVertex(v1p,n4);
    pVertex(v3,n4);
    pVertex(v3p,n4);
	EndPrimitive();
	
	
	//Triangulo atras 1
	pVertex(v2,n5);
    pVertex(v2p,n5);
    pVertex(v3,n5);
    pVertex(v3p,n5);
	EndPrimitive();
	
    
}
