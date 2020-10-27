#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
in vec3 vnormal[];
out vec4 gfrontColor;

uniform float time;

uniform mat4 modelViewProjectionMatrix;

vec3 normal() {
	return vec3((vnormal[0].x + vnormal[1].x + vnormal[2].x)/3,(vnormal[0].y + vnormal[1].y + vnormal[2].y)/3,(vnormal[0].z + vnormal[1].z + vnormal[2].z)/3);
}

void main( void )
{
	const float speed = 0.5;
	for( int i = 0 ; i < 3 ; i++ )
	{
		vec4 p = gl_in[i].gl_Position;
		p.x += normal().x * time * speed;
		p.y += normal().y * time * speed;
		p.z += normal().z * time * speed;
		gl_Position = modelViewProjectionMatrix  * p;
		gfrontColor = vfrontColor[i];
		EmitVertex();
	}
    EndPrimitive();
}
