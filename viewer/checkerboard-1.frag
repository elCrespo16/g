#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

void main()
{
	
	float octavo = 1./8.;
	float sum = vtexCoord.s*8+vtexCoord.t*8;
	//if(mod(sum,2.) < 1)
	if(mod(vtexCoord.s*8,2.) < 1){
		if(mod(vtexCoord.t*8,2.) < 1)fragColor = vec4 (0.8);
		else fragColor = vec4 (0.0);
		//< 1 && mod(vtexCoord.t*8,2.) < 1) 
	}
	else{
	 if(!(mod(vtexCoord.t*8,2.) < 1))fragColor = vec4 (0.8);
	 else fragColor = vec4 (0.0);
	}
    //fragColor = frontColor;
}
