#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "plugin.h" 
#include <QElapsedTimer>

class Framerate: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

  private:
	// add private methods and attributes here
	QElapsedTimer elapsedTimer;
	int frames = 0;
};

#endif
