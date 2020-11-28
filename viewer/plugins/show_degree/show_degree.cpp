#include "show_degree.h"
#include "glwidget.h"

void Show_degree::onPluginLoad()
{
	int nVertex = scene() -> objects()[0].vertices().size();
	const vector< Face > f = scene() -> objects()[0].faces();
	int nFaces = f.size(), numV = 0;
	for(int i = 0; i < nFaces;++i){
		numV += f[i].numVertices();
	}
	res = float(numV) / nVertex;
}

void Show_degree::postFrame()
{
	cout << "Degree de los verices medio: " << res << endl;
}


