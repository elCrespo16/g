#version 330 core
        
layout(triangles) in;
layout(triangle_strip, max_vertices = 36) out;

in vec4 vfrontColor[];

uniform mat4 modelViewProjectionMatrix;
uniform vec3 boundingBoxMin;
uniform vec3 boundingBoxMax;
out vec4 gfrontColor;

vec3 boundingBoxCenter() {
	return vec3((boundingBoxMax.x + boundingBoxMin.x)/2,boundingBoxMin.y, (boundingBoxMax.z + boundingBoxMin.z)/2);
}

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
	EndPrimitive();
	
	if(gl_PrimitiveIDIn == 0) {
		gfrontColor = vec4(0.,1.0,1.0,.0);
		float R = distance(boundingBoxMin, boundingBoxMax);
		float y = 0.01;
		vec3 boundingCenter = boundingBoxCenter();
		gl_Position = modelViewProjectionMatrix * vec4(boundingCenter.x - R/2,boundingBoxMin.y-y,boundingCenter.z - R/2,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(boundingCenter.x + R/2,boundingBoxMin.y-y,boundingCenter.z - R/2,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(boundingCenter.x - R/2,boundingBoxMin.y-y,boundingCenter.z + R/2,1); EmitVertex();
		gl_Position = modelViewProjectionMatrix * vec4(boundingCenter.x + R/2,boundingBoxMin.y-y,boundingCenter.z + R/2,1); EmitVertex();
		EndPrimitive();
	}
}
