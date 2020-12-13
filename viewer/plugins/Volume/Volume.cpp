#include "Volume.h"
#include "glwidget.h"

void Volume::onPluginLoad()
{
	const vector< Face > f = scene() -> objects()[0].faces();
	const vector< Vertex > v = scene() -> objects()[0].vertices();
	int nFaces = f.size();
	float res = 0;
	for(int i = 0; i < nFaces;++i){
		float n = f[i].normal().z();
		float c = 0;
		float a = 0;
		Vector v1;
		Vector v2;
		Vertex p1 = v[f[i].vertexIndex(0)];
		Vertex p2 = v[f[i].vertexIndex(1)];
		Vertex p3 = v[f[i].vertexIndex(2)];
		v1 = Vector(p2.coord().x()-p1.coord().x(),p2.coord().y()-p1.coord().y(),p2.coord().z()-p1.coord().z());
		v2 = Vector(p3.coord().x()-p1.coord().x(),p3.coord().y()-p1.coord().y(),p3.coord().z()-p1.coord().z());
		c = p1.coord().z()+ p2.coord().z()+ p3.coord().z();
		c = c/3;
		a = QVector3D::crossProduct(v1,v2).length()/2;
		res += n*c*a;
	}
	cout << "Volumen: "<< res<<endl;
}

