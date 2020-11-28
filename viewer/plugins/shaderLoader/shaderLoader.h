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

#ifndef _SHADERLOADER_H
#define _SHADERLOADER_H

#include "plugin.h"
#include "glwidget.h"
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>
#include <QDateTime>
#include <QElapsedTimer>
#include <QWidget>
#include <map>
using namespace std;

class ShaderLoader : public QObject, public Plugin 
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "Plugin")   
    Q_INTERFACES(Plugin)

    public:
  ShaderLoader();
  ~ShaderLoader();
  void onPluginLoad();
  bool paintGL();
  void keyPressEvent(QKeyEvent*);   
  void createDefaultShaders(bool createAlsoGS); 

  public slots:
    void createDefaultShadersVSFS(); 
    void createDefaultShadersVSGSFS(); 
    
    void createShaderFromTemplate();

    void attachShaders();
    void attachShaders(QString name);
    void openFilesInTextEditor();
    void switchStatusVS();
    void switchStatusGS();
    void switchStatusFS();
    void switchStatusWireframe();
    void switchStatusShowAxes();
    void switchStatusShowLight();

    void resetCamera();
    void cameraPreset1();
    void cameraPreset2();
    void cameraPreset3();
    void cameraPreset4();
    void cameraPreset5();

    void loadObject();
    void loadObject(const QString& file);


    void changeBackgroundColor();
    void loadTexture0();
    void loadTexture1();
    void loadTexture2();
    void loadTexture3();
    void showTextures();

    /* void setLights(); */
    void setLightAmbient();
    void setLightDiffuse();
    void setLightSpecular();
    void setLightPositionWorld();
    void setLightPositionEye();
    void resetLightPosition();
    void switchLightRotate();

    /* void setMaterials(); */
    void setMaterialAmbient();
    void setMaterialDiffuse();
    void setMaterialSpecular();

    void editUniform(int id);
    void uniformMult(bool up); // double/half active uniform

    QString executeTest();
    void compareTest();


 private:

    void loadTexture(int unit, QString filename=QString());
    void drawHelp();
    

    void reloadShaders();
    void checkForUpdates();
    void showMenu(const QPoint&);

    bool isPredefinedUniform(QString name);
    void uniformValueToString(int id, QString& value, QString& typeName);

    bool showHelp;

    // test mode
    bool testMode;
    vector<QString> testUniformIntNames;
    vector<QString> testUniformFloatNames;
    vector<QString> testUniformBoolNames;
    vector<int> testUniformIntValues;
    vector<float> testUniformFloatValues;
    vector<bool> testUniformBoolValues;

    //GLuint textureId;

    QString filename; // "animate_vertices"
    QOpenGLShaderProgram* program;
    QOpenGLShader* vs;
    QOpenGLShader* gs;
    QOpenGLShader* fs;

    bool enabled_vs; 
    bool enabled_gs; 
    bool enabled_fs; 

    bool wireframe;
    bool showAxes;
    bool showLight;

    Vector backgroundColor;

    Vector lightAmbient;
    Vector lightDiffuse;
    Vector lightSpecular;
    QVector4D lightPosition;   // eye space or world space, depending on boolean
    bool lightEncodedInEyeSpace; 
    bool lightRotate; // auto-rotation

    Vector materialAmbient;
    Vector materialDiffuse;
    Vector materialSpecular;
    float materialShininess;

    GLuint textureID[4];
    QString textureName[4];

    QDateTime lastModifiedVS;
    QDateTime lastModifiedGS;
    QDateTime lastModifiedFS;

    QElapsedTimer elapsedTimer;
    QTimer timer; 

    vector<QString> predefinedUniforms;
    int activeUniform; // uniform that can be edited with the keyboard
    //map<QString,

    bool grading;
    string gradeShader;
};
 
#endif

