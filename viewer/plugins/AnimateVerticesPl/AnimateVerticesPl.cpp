#include "AnimateVerticesPl.h"
#include "glwidget.h"

void AnimateVerticesPl::onPluginLoad()
{
	//Cargar, compilar y montar el shader
	vs = new QOpenGLShader(QOpenGLShader::Vertex,this);
	vs -> compileSourceFile("../../ejercicio1.vert");
	fs = new QOpenGLShader(QOpenGLShader::Fragment,this);
	fs -> compileSourceFile("../../ejercicio1.frag");
	program = new QOpenGLShaderProgram(this);
	program -> addShader(vs);
	program -> addShader(fs);
	program -> link();
	elapsedTimer.start();
}

void AnimateVerticesPl::preFrame()
{
	//Bindear y enviar uniforms
	program -> bind();
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    QMatrix3x3 NM = camera()->viewMatrix().normalMatrix();
    program->setUniformValue("normalMatrix", NM);
	program -> setUniformValue("time",float(elapsedTimer.elapsed()/1000.0f));
}

void AnimateVerticesPl::postFrame()
{
	program -> release();
	//Unbindear
}

