#include "modelInfo2.h"
#include "glwidget.h"

void ModelInfo2::postFrame()
{
	/*
	Se podria hacer mucho mas eficiente, calculando cada vez que se añade un objeto su numero de poligons y mantenerlo como
	variable global, pero para este ejercicio creo que no es necesario xd
	*/
	Scene* sc = scene();
	const vector<Object> obj = (*sc).objects();
	int size = obj.size(), poligons = 0, triangles = 0;
	for(int i = 0; i < size;++i){
		const vector< Face > f = obj[i].faces();
		int faces_size = f.size();
		poligons += faces_size;
		for(int j = 0; j < faces_size;++j){
			if(f[i].numVertices() == 3) ++triangles;
		}
	}
	QFont font;
  	font.setPixelSize(32);
  	painter.begin(glwidget());
  	painter.setFont(font);
  	int x = 15;
  	int y = 40;
  	string res = "Numero de poligonos: " + to_string(poligons); 
  	int n = res.length();
  	char char_array[n+1]; 
  	strcpy(char_array,res.c_str());
  	painter.drawText(x, y, QString(char_array));
  	string res2 = "Porcentage de triangulos: " + to_string(triangles * 100 / poligons);
  	int n2 = res2.length(); 
  	char char_array2[n2+1];
  	strcpy(char_array2,res2.c_str());
  	painter.drawText(15, 90, QString(char_array2));
  	
  	painter.end();
}


