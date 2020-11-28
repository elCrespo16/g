#include "drawSmooth.h"
#include "glwidget.h"

DrawSmooth::~DrawSmooth() {
  cleanUp();
}

void DrawSmooth::onSceneClear()
{
    cleanUp();
}

void DrawSmooth::cleanUp()
{
  GLWidget &g = *glwidget();
  g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
  g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
  g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
  g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
  g.glDeleteBuffers(indexBuffers.size(),  &indexBuffers[0]);
  g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
  coordBuffers.clear();
  normalBuffers.clear();
  stBuffers.clear();
  colorBuffers.clear();
  VAOs.clear();
  numIndices.clear();
}

bool DrawSmooth::drawObject(int i)
{
  GLWidget &g = *glwidget();
  g.makeCurrent();
  g.glBindVertexArray(VAOs[i]);
  g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, 0);
  g.glBindVertexArray(0);
  return true;
}

bool DrawSmooth::drawScene()
{
  GLWidget &g = *glwidget();
  g.makeCurrent();
  for(unsigned int i=0; i<VAOs.size(); i++) // for each buffer (that is, for each object)
	drawObject(i);
  return true;
}

void DrawSmooth::onPluginLoad()
{
  for(unsigned int i=0; i<scene()->objects().size(); i++)
    addVBO(i);
}

void DrawSmooth::onObjectAdd()
{
  addVBO( scene()->objects().size() - 1 );
}

void DrawSmooth::addVBO(unsigned int currentObject)
{
  //
  // For simplicity, we construct VBOs with replicated vertices (a copy
  // for each triangle to which they belong:
  //
  GLWidget& g = *glwidget();
	g.makeCurrent();
  const Object& obj = scene()->objects()[currentObject];
  vector<float> vertices; // (x,y,z)    Final size: 9*number of triangles
  vector<float> normals;  // (nx,ny,nz) Final size: 9*number of triangles
  vector<float> colors;   // (r, g, b)  Final size: 9*number of triangles
  vector<float> texCoords;// (s, t)     Final size: 6*number of triangles
  vector<int> indices;
  int numFaces = obj.faces().size();
  for(int i = 0;i < numFaces;++i){
  	int fsize = obj.faces()[i].numVertices();
  	for(int j = 0;j < fsize;++j){
  		cout << obj.faces()[i].vertexIndex(j) << endl;
  		indices.push_back(obj.faces()[i].vertexIndex(j));
  	}
  }
  cout << "indices usados "<< indices.size() << endl;
  cout << "vertices totales " << obj.vertices().size() << endl;
  for(int i = 0;i < obj.vertices().size();++i){
  	vertices.push_back(obj.vertices()[i].coord().x());
  	vertices.push_back(obj.vertices()[i].coord().y());
  	vertices.push_back(obj.vertices()[i].coord().z());
  	normals.push_back(obj.vertNormals()[i].x());
  	normals.push_back(obj.vertNormals()[i].y());
  	normals.push_back(obj.vertNormals()[i].z());
  	colors.push_back(obj.vertNormals()[i].x());
  	colors.push_back(obj.vertNormals()[i].y());
  	colors.push_back(obj.vertNormals()[i].z());
  	/*colors.push_back(0.);
  	colors.push_back(0.);
  	colors.push_back(0.);*/
  	texCoords.push_back(obj.vertTexCoords()[i].first);
  	texCoords.push_back(obj.vertTexCoords()[i].second);
  }

  // Step 2: Create VAO and empty buffers (coords, normals, ...)
  GLuint VAO;
  g.glGenVertexArrays(1, &VAO);
  VAOs.push_back(VAO);
  cout << "VAO " << VAO; 
  g.glBindVertexArray(VAO);
  
  GLuint coordBufferID;
  g.glGenBuffers(1, &coordBufferID);
  coordBuffers.push_back(coordBufferID);
  cout << "coordBufferID " << coordBufferID << endl; 
  
  GLuint normalBufferID;
  g.glGenBuffers(1, &normalBufferID);
  normalBuffers.push_back(normalBufferID);
  cout << "normalBufferID " << normalBufferID << endl; 
  
  GLuint stBufferID;
  g.glGenBuffers(1, &stBufferID);
  stBuffers.push_back(stBufferID);
  cout << "stBufferID " << stBufferID << endl; 
  
  GLuint colorBufferID;
  g.glGenBuffers(1, &colorBufferID);
  colorBuffers.push_back(colorBufferID);
  cout << "colorBufferID " << colorBufferID << endl; 
  
  GLuint indicesID;
  g.glGenBuffers(1, &indicesID);
  indexBuffers.push_back(indicesID);
  cout << "indicesID " << indicesID << endl; 
  
  numIndices.push_back(indices.size());
  // Step 3: Define VBO data (coords, normals, ...)
  g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
  g.glEnableVertexAttribArray(0);

  g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(1);

  g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(2);

  g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(3);
  
 
  g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
  g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);
  
  g.glBindBuffer(GL_ARRAY_BUFFER,0);
  g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
  g.glBindVertexArray(0);
}
