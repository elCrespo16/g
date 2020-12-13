#include "framerate.h"
#include "glwidget.h"

void Framerate::onPluginLoad()
{
	elapsedTimer.start();
}

void Framerate::preFrame()
{
	cout << "Frames: " << frames / float(elapsedTimer.elapsed()/1000.0f) << endl;
}

void Framerate::postFrame()
{
	++frames;
}

