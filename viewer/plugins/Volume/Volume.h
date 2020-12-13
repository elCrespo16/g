#ifndef _VOLUME_H
#define _VOLUME_H

#include "plugin.h" 

class Volume: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
  private:
	// add private methods and attributes here
};

#endif
