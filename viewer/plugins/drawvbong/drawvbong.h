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

#ifndef _DRAW_VBONG_H
#define _DRAW_VBONG_H

#include <vector>
#include "plugin.h"

using namespace std;

class DrawVBOng : public QObject, public Plugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")   
  Q_INTERFACES(Plugin)

 public:
  ~DrawVBOng();
  void cleanUp();
 
  void onSceneClear();
  void onPluginLoad();
  void onObjectAdd();
  bool drawScene();
  bool drawObject(int);
   
 private:
  void addVBO(unsigned int currentObject);

  // We will create a VBO for each object in the scene
  vector<GLuint> VAOs;          // ID of VAOs
  vector<GLuint> coordBuffers;  // ID of vertex coordinates buffer 
  vector<GLuint> normalBuffers; // ID of normal components buffer 
  vector<GLuint> stBuffers;     // ID of (s,t) buffer 
  vector<GLuint> colorBuffers;  // ID of color buffer  
  vector<GLuint> numIndices;    // Size (number of indices) in each index buffer
};
 
#endif
