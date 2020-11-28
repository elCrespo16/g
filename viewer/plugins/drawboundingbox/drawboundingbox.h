#ifndef _DRAWBOUNDINGBOX_H
#define _DRAWBOUNDINGBOX_H

#include "plugin.h" 

class Drawboundingbox: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
	 void preFrame();
  private:
  	void SetUpShaders();
  	void CreateBox();
  	GLuint VAO;
  	QOpenGLShaderProgram* program;
	QOpenGLShader *fs, *vs;
	// add private methods and attributes here
};

#endif
