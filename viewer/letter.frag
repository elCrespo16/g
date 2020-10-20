#version 330 core

in vec4 frontColor;
in vec2 vtexCoord;
out vec4 fragColor;

bool F0 [5];
bool F1 [5];
bool F2 [5];
bool F3 [5];
bool F4 [5];
bool F5 [5];
bool F6 [5];

void fill(){
for(int i = 0; i < 5;++i){
	F0[0] = false;
	F1[0] = false;
	F2[0] = false;
	F3[0] = false;
	F4[0] = false;
	F5[0] = false;
	F6[0] = false;
	}
	F0[0] = true;
	F1[0] = true;
	F2[0] = true;
	F3[0] = true;
	F4[0] = true;
	F5[0] = true;
	F6[0] = true;
	for(int i = 0; i < 5;++i){
		F0[i] = true;
	}
	for(int i = 0; i < 3;++i){
		F3[i] = true;
	}
}

bool printable(){
	int x = int(fract(vtexCoord.s)*10.)%4;
	int y = int(fract(vtexCoord.t)*10.)%6;
	if(x < 4){
		if(y == 0) return F0[x];
		if(y == 1) return F1[x];
		if(y == 2) return F2[x];
		if(y == 3) return F3[x];
		if(y == 4) return F4[x];
		if(y == 5) return F5[x];
		if(y == 6) return F6[x];
	}
	return false;
}

void main()
{
	vec4 black = vec4(0.,0.,0.,0.);
	vec4 white = vec4(1.,1.,1.,0.);
	//fill();
	//if(printable()) fragColor = black;
	//else fragColor = white;
	float x = fract(vtexCoord.s);
	float y = fract(vtexCoord.t);
	float slice = 1./7.;
    if(x < slice) fragColor = black;
    else if(y > slice*6) fragColor = black;
    else if(x < slice*5 && y < slice*4 && y > slice*3)fragColor = black;
    else fragColor = white;
    //fragColor = frontColor;
}
