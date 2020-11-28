#ifndef _SHOW_DEGREE_H
#define _SHOW_DEGREE_H

#include "plugin.h" 

class Show_degree: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void postFrame();
  private:
  	float res;
	// add private methods and attributes here
};

#endif
