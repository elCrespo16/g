#include "ModelInfo.h"
#include "glwidget.h"

void ModelInfo::postFrame()
{
	/*
	Se podria hacer mucho mas eficiente, calculando cada vez que se añade un objeto su numero de poligons y mantenerlo como
	variable global, pero para este ejercicio creo que no es necesario xd
	*/
	Scene* sc = scene();
	const vector<Object> obj = (*sc).objects();
	int size = obj.size(), poligons = 0, triangles = 0;
	cout << "Total objetos cargados: " << size << endl;
	for(int i = 0; i < size;++i){
		const vector< Face > f = obj[i].faces();
		int faces_size = f.size();
		poligons += faces_size;
		for(int j = 0; j < faces_size;++j){
			if(f[i].numVertices() == 3) ++triangles;
		}
	}
	cout << "Numero de poligonos: " << poligons << endl;
	cout << "Porcentage de triangulos: " << (triangles * 100) / poligons << endl;
	
}

