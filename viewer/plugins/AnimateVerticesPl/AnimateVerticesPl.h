#ifndef _ANIMATEVERTICESPL_H
#define _ANIMATEVERTICESPL_H

#include "plugin.h" 
#include <QElapsedTimer>

class AnimateVerticesPl: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();
  private:
	QOpenGLShaderProgram* program;
	QOpenGLShader *fs, *vs;
	QElapsedTimer elapsedTimer;
};

#endif
