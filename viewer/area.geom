#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

uniform mat4 projectionMatrix;
out vec4 gfrontColor;
const float areamax = 0.0005;
const vec4 red = vec4(1.,0.,0.,0.);
const vec4 yellow = vec4(1.,1.,0.,0.);

float area() {
	vec3 cross = cross((gl_in[1].gl_Position-gl_in[0].gl_Position).xyz,(gl_in[2].gl_Position-gl_in[0].gl_Position).xyz);
	return length(cross)/2;
}

void main( void )
{
	float a = area() / areamax;
	if(a >= 1.0) gfrontColor = yellow;
	else gfrontColor = mix(red,yellow,fract(a));
	for( int i = 0 ; i < 3 ; i++ )
	{
		gl_Position = projectionMatrix*gl_in[i].gl_Position;
		EmitVertex();
	}
    EndPrimitive();
}
