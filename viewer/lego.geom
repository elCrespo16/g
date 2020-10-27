#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform sampler2D colorMap;

in vec4 vfrontColor[];
in vec3 Nnormal[];
out float gNormal;
out vec2 gtexCoord;
out vec4 gfrontColor;
out vec3 gNnormal;
uniform float step = 0.5;
uniform mat4 modelViewProjectionMatrix;

void addVertex(float a, float b, float c, bool top, vec3 center) {
	if(top) {
	 	gNormal = 1.0;
	 	gtexCoord = vec2(a/2, c/2);
	}
	else {
		gNormal = 0.0;
		gtexCoord = vec2(0.0,0.0);
	}
	gl_Position = modelViewProjectionMatrix * vec4(center.x + a*0.5*step,center.y+b*0.5*step,center.z+c*0.5*step,1.0);
	EmitVertex();
}

vec3 center() {
	vec3 center = vec3((gl_in[0].gl_Position.xyz+gl_in[1].gl_Position.xyz+gl_in[2].gl_Position.xyz)/3);
	center /= step;
	center.x=int(center.x);
  	center.y=int(center.y);
  	center.z=int(center.z);
  	center*=step;
  	return center;
}

void main( void )
{
	gfrontColor = (vfrontColor[0]+vfrontColor[1]+vfrontColor[2])/3;
	gNnormal = (Nnormal[0]+Nnormal[1]+Nnormal[2])/3;
	//gNnormal = Nnormal[2];
	vec3 center = center();
	
	//Cara 1
	addVertex(+1.0, +1.0, +1.0, false, center);
	addVertex(-1.0, +1.0, +1.0, false, center);
	addVertex(+1.0, -1.0, +1.0, false, center);
	addVertex(-1.0, -1.0, +1.0, false, center);
	EndPrimitive();
	//Cara 2
	addVertex(+1.0, +1.0, +1.0, false, center);
	addVertex(+1.0, +1.0, -1.0, false, center);
	addVertex(+1.0, -1.0, +1.0, false, center);
	addVertex(+1.0, -1.0, -1.0, false, center);
	EndPrimitive();
	//Cara 3 Arriba
	addVertex(+1.0, +1.0, +1.0, true, center);
	addVertex(-1.0, +1.0, +1.0, true, center);
	addVertex(+1.0, +1.0, -1.0, true, center);
	addVertex(-1.0, +1.0, -1.0, true, center);
	EndPrimitive();
	//Cara 1
	addVertex(-1.0, -1.0, -1.0, false, center);
	addVertex(+1.0, -1.0, -1.0, false, center);
	addVertex(-1.0, +1.0, -1.0, false, center);
	addVertex(+1.0, +1.0, -1.0, false, center);
	EndPrimitive();
	//Cara 2
	addVertex(-1.0, -1.0, -1.0, false, center);
	addVertex(-1.0, -1.0, +1.0, false, center);
	addVertex(-1.0, +1.0, -1.0, false, center);
	addVertex(-1.0, +1.0, +1.0, false, center);
	EndPrimitive();
	//Cara 3
	addVertex(-1.0, -1.0, -1.0, false, center);
	addVertex(+1.0, -1.0, -1.0, false, center);
	addVertex(-1.0, -1.0, +1.0, false, center);
	addVertex(+1.0, -1.0, +1.0, false, center);
	EndPrimitive();
}

