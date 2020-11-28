// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#ifndef _PluginLoader_H
#define _PluginLoader_H

#include "plugin.h"
#include "glwidget.h"
#include <QDateTime>

using namespace std;

class PluginLoader : public QObject, public Plugin 
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")   
  Q_INTERFACES(Plugin)

 public:
  PluginLoader();
  void onPluginLoad();
  void postFrame();
  void keyPressEvent(QKeyEvent*);

 public slots:
   void createDefaultPlugin(); 
   void createPluginFromTemplate();
   void attachPlugin();
   void attachPlugin(QString name);
   void openFilesInTextEditor();

   void resetCamera();
   void cameraPreset1();
   void cameraPreset2();
   void cameraPreset3();
   void cameraPreset4();
   void cameraPreset5();
   
   void loadObject();
   void loadObject(const QString& file);

   //QString executeTest();
   //void compareTest();

 private:

   int  currentPlugin;
   void reloadPlugin();
   void checkForUpdates();
   void showMenu(const QPoint&);

   QString filename; // "animate_vertices"
   bool pluginEnabled;
   int pluginVersion;
   
   QDateTime lastModifiedH;
   QDateTime lastModifiedCPP;

   QTimer timer;
   QString origCWD;
   QString qmakePath;
   qint64 graceTime; // how many msecs. after saving to recompile.
};

#endif
