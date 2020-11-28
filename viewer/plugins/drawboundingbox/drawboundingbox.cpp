#include "drawboundingbox.h"
#include "glwidget.h"

void Drawboundingbox::SetUpShaders()
{
	vs = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vs -> compileSourceFile("./ejercicio1.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs -> compileSourceFile("./ejercicio1.frag");
	program = new QOpenGLShaderProgram(this);
	program -> addShader(vs);
	program -> addShader(fs);
	program -> link();
}

void Drawboundingbox::CreateBox(){
GLWidget& g = *glwidget();
	g.makeCurrent();
  	g.glGenVertexArrays(1, &VAO);
  	g.glBindVertexArray(VAO);
	float vertices[] = {0,0,0, 
	0,1,0,
	0,1,1,
	0,0,1,
	1,0,1,
	1,0,0,
	1,1,0,
	1,1,1
	};
	//float vertices[] = {1,0,1,1,1,1};
	GLuint coordBufferID;
  g.glGenBuffers(1, &coordBufferID);
  g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
  g.glEnableVertexAttribArray(0);
	GLuint indices[] = {
	0,1,
	1,2,
	2,3,
	3,0,
	3,4,
	4,5,
	5,0,
	5,6,
	6,1,
	6,7,
	7,2,
	7,4
	};
  	GLuint indicesID;
  g.glGenBuffers(1, &indicesID);
  g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesID);
  g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
  g.glBindVertexArray(0);
}

void Drawboundingbox::onPluginLoad()
{
	SetUpShaders();
	CreateBox();
}


void Drawboundingbox::preFrame(){
	
	
}

void Drawboundingbox::postFrame()
{
	program -> bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
	Scene* sc = scene();
	const vector<Object> obj = (*sc).objects();
	GLWidget &g = *glwidget();
  	g.makeCurrent(); 
	for(int i = 0;i < obj.size();++i){
		program->setUniformValue("boundingBoxMin",obj[i].boundingBox().min());
		program->setUniformValue("boundingBoxMax",obj[i].boundingBox().max());
		g.glBindVertexArray(VAO);
		//g.glDrawArrays(GL_LINES,0,2);
		g.glDrawElements(GL_LINES, 24, GL_UNSIGNED_INT, 0);
		g.glBindVertexArray(0);
	}
  program -> release();
  
}

