#version 330 core

uniform sampler2D colorTex;

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

vec4 yellow = vec4(1.,1.,0.,1.);
vec4 red = vec4(1.,0.,0.,1.);
vec4 blue = vec4(0.,0.,1.,1.);
vec4 pink = vec4(1.,0.,1.,1.);
vec4 orange = vec4(1.,0.5,0.25,1.);
float slice = 1./6;

bool between(float x, float a, float b){
	return x >= a && x <= b;
}

bool pared(float x, float y){
	for(int i = 0; i < 6; ++i){
		if(between(x,1./3,2./3) && between(y,slice*i,slice*i+0.01)) return true;
	}
	return false;
}

bool moneda (float x, float y){
	float slice1 = 1./12;
	for(int i = 0; i < 12; ++i){
		for(int j = 0; j < 12; ++j){
			if(distance(vec2(x,y),vec2(slice1*i, slice1*j)) < 0.01 && i % 2 != 0 && j % 2 != 0) return true;
		}
	}
	return false;
}

void main()
{
	float pacmanX = 2./6;
	float pacmanY = 0;
	float f1X = 4./6;
	float f1Y = 3./6;
	float f2X = 5./6;
	float f2Y = 2./6;
	float f3X = 0./6;
	float f3Y = 5./6;
	float f4X = 1./6;
	float f4Y = 1./6;
	//Pacman position
	if(between(vtexCoord.s,pacmanX,pacmanX+slice) && between(vtexCoord.t,pacmanY,pacmanY+slice)) {
		fragColor = texture(colorTex,vec2(vtexCoord.s*3+0.5,vtexCoord.y*6));
	}
	//Fantasma 1
	else if(between(vtexCoord.s,f1X,f1X+slice) && between(vtexCoord.t,f1Y,f1Y+slice)){
		fragColor = texture(colorTex,vec2((vtexCoord.s-f1X)*3,vtexCoord.t*6));
	}
	//Fantasma 2
	else if(between(vtexCoord.s,f2X,f2X+slice) && between(vtexCoord.t,f2Y,f2Y+slice)){
		vec4 col = texture(colorTex,vec2((vtexCoord.s - f2X)*3,vtexCoord.t*6));
		if(col == red) fragColor = blue;
		else fragColor = col;
	}
	//Fantasma 3
	else if(between(vtexCoord.s,f3X,f3X+slice) && between(vtexCoord.t,f3Y,f3Y+slice)){
		vec4 col = texture(colorTex,vec2((vtexCoord.s - f3X)* 3,vtexCoord.t*6));
		if(col == red) fragColor = pink;
		else fragColor = col;
	}
	//Fantasma 4
	else if(between(vtexCoord.s,f4X,f4X+slice) && between(vtexCoord.t,f4Y,f4Y+slice)){
		vec4 col = texture(colorTex,vec2((vtexCoord.s-f4X)*3,vtexCoord.t*6));
		if(col == red) fragColor = orange;
		else fragColor = col;
	}
	//Paredes
	else if(pared(vtexCoord.s,vtexCoord.t)){
		fragColor = blue;
	}
	//Monedas
	else if(moneda(vtexCoord.s,vtexCoord.t)) {
		fragColor = yellow;
	}
	else {
		fragColor = vec4(0);
	}
    
}
