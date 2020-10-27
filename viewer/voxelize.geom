#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform sampler2D colorMap;

in vec4 vfrontColor[];
in vec2 vtexCoord[];
out float gNormal;
out vec4 gfrontColor;
out vec2 gtexCoord;
uniform float step = 0.2;
uniform mat4 modelViewProjectionMatrix;

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
	gtexCoord = vtexCoord[0];
	gfrontColor = (vfrontColor[0]+vfrontColor[1]+vfrontColor[2])/3;
	vec3 center = center();
	gNormal = 0.0;
	//Cara 1
	gl_Position = modelViewProjectionMatrix * vec4(center.xyz+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y+0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y-0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y-0.5*step,center.z+0.5*step,1.0);EmitVertex();
	EndPrimitive();
	//Cara 2
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y+0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y+0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y-0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y-0.5*step,center.z-0.5*step,1.0);EmitVertex();
	EndPrimitive();
	//Cara 3 Arriba
	gNormal = 1.0;
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y+0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y+0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y+0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y+0.5*step,center.z-0.5*step,1.0);EmitVertex();
	EndPrimitive();
	gNormal = 0.0;
	//Cara 1
	gl_Position = modelViewProjectionMatrix * vec4(center.xyz-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y-0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y+0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y+0.5*step,center.z-0.5*step,1.0);EmitVertex();
	EndPrimitive();
	//Cara 2
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y-0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y-0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y+0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y+0.5*step,center.z+0.5*step,1.0);EmitVertex();
	EndPrimitive();
	//Cara 3
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y-0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y-0.5*step,center.z-0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x - 0.5*step,center.y-0.5*step,center.z+0.5*step,1.0);EmitVertex();
	gl_Position = modelViewProjectionMatrix * vec4(center.x + 0.5*step,center.y-0.5*step,center.z+0.5*step,1.0);EmitVertex();
	EndPrimitive();
}

