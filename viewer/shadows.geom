#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];
out vec4 gfrontColor;

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;

void main( void )
{
	//Tringulo normal
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vfrontColor[i];
		gl_Position = modelViewProjectionMatrix*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
    //Triangulo X = 0
    for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0.);
		gl_Position = gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix*vec4(boundingBoxMin.x,gl_Position.y,gl_Position.z,gl_Position.w);
		EmitVertex();
	}
	EndPrimitive();
	//Triangulo Y = 0
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0.);
		gl_Position = gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix*vec4(gl_Position.x,boundingBoxMin.y,gl_Position.z,gl_Position.w);
		EmitVertex();
	}
	EndPrimitive();
	//Triangulo Z = 0
	for( int i = 0 ; i < 3 ; i++ )
	{
		gfrontColor = vec4(0.);
		gl_Position = gl_in[i].gl_Position;
		gl_Position = modelViewProjectionMatrix*vec4(gl_Position.x,gl_Position.y,boundingBoxMin.z,gl_Position.w);
		EmitVertex();
	}
	EndPrimitive();
}
