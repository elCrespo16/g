#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
out vec4 gfrontColor;

void main( void )
{
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix  * gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    gfrontColor = vec4(0.);
    for( int i = 0 ; i < 3 ; i++ )
	{	
		vec4 p = gl_in[i].gl_Position;
		p.y = boundingBoxMin.y;
		gl_Position = modelViewProjectionMatrix  * p;
		EmitVertex();
	}
}
