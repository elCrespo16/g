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

#include "shaderLoader.h"
#include <QDir>
#include <QMenu>
#include <QProcess>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QPainter>
#include "customdialog.h"
#include <fstream>
#include <sstream>
#include <cmath>
#ifndef __APPLE__
  #include <GL/glu.h>
#else
  #include <glu.h>
#endif
#include <iostream>
ShaderLoader::ShaderLoader()
{
    vs=gs=fs=0;
    program=0;
    showHelp = true;
    filename = "";
    enabled_vs = enabled_fs = true;
    enabled_gs = false;
    wireframe = false;
    showAxes = true;
    showLight = true;
    backgroundColor = Vector(1,1,1);
    textureID[0]=textureID[1]=textureID[2]=textureID[3] = 0;
    textureName[0]=textureName[1]=textureName[2]=textureName[3]=QString();
    activeUniform = -1;
    testMode = false;
    grading = false;
}

ShaderLoader::~ShaderLoader() 
{
    // clean up
    if (vs) delete vs;
    if (gs) delete gs;
    if (fs) delete fs;
    if (program) delete program;
}

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << endl;

int printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
			     file, line, gluErrorString(glErr), func);
        retCode = 1;
    }
    return retCode;
}


void ShaderLoader::onPluginLoad()
{
    glwidget()->makeCurrent();
    connect(&timer, SIGNAL(timeout()), glwidget(), SLOT(update()));
    timer.start();
    elapsedTimer.start();

    lightAmbient = Vector(0.1,0.1,0.1);
    lightDiffuse = Vector(1,1,1);
    lightSpecular = Vector(1,1,1);

    lightPosition = QVector4D(0,0,0,1);
    lightEncodedInEyeSpace = true;
    lightRotate = false;

    materialAmbient = Vector(0.8, 0.8, 0.6);
    materialDiffuse = Vector(0.8, 0.8, 0.6);
    materialSpecular = Vector(1.0, 1.0, 1.0);
    materialShininess = 64.0;
    

    QString textures = "/assig/grau-g/Textures";
    char* tmp = getenv ("VTEXTURES");
    if (tmp!=NULL) textures=QString(tmp);
    loadTexture(0,textures+"/default.png");
    string::size_type gradepos =  args().find("--grade-shader ");
    if (gradepos != string::npos) {
      gradepos += args().substr(gradepos+15).find_first_not_of(" ");
      grading = true;
      int nameLength = args().substr(gradepos+15).find_first_of(" .");
      gradeShader = args().substr(gradepos+15, nameLength);
      std::cout << "Detected flag to grade `" << gradeShader <<"'"<< std::endl;
    }
}



void ShaderLoader::keyPressEvent(QKeyEvent*e)
{
  GLWidget &g =*glwidget();
  if (e->key() == Qt::Key_Space) showMenu(QCursor::pos());
  g.makeCurrent();
  if (e->key() == Qt::Key_O)
    {
      attachShaders();
    } 
  if (e->key() == Qt::Key_S) 
    {
        QImage img = g.grabFramebuffer();
        QDateTime time = QDateTime::currentDateTime();
        QString name = QString("Snap-") + time.toString("yyyy-MM-dd----hh:mm:ss") + QString(".png");
        img.save(name);
        cout << "Image saved" << endl;
    }
  if (e->key() == Qt::Key_T) executeTest();
  if (e->key() == Qt::Key_C) 
    {
        compareTest();
    }
  if (e->key() == Qt::Key_Up) uniformMult(true);
  if (e->key() == Qt::Key_Down) uniformMult(false);
  if (e->key() == Qt::Key_Z) elapsedTimer.start();
}

const int ID_OFFSET = 10;

bool ShaderLoader::isPredefinedUniform(QString name)
{
    //return false;
  
    if (name.startsWith("gl_")) return true;
    for (unsigned int i=0; i<predefinedUniforms.size(); ++i)
        if (predefinedUniforms[i]==name) return true;
    return false;
}

void ShaderLoader::uniformValueToString(int id, QString& value, QString& typeName)
{
    GLWidget& g = *glwidget();
    program->bind();

    GLchar name[500];
    GLsizei length;
    GLint size;
    GLenum type;
    g.glGetActiveUniform (program->programId(), id, 500, &length, &size, &type, &name[0]);

    //cout << i << " " << name << " Size: " << size << " Type: " << type << endl;

    GLint MAX;
    g.glGetProgramiv(program->programId(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &MAX);
    GLint iparams[MAX];
    GLfloat fparams[MAX];
    value="";
    typeName=""; 


    // 	GL_FLOAT, 	GL_FLOAT_VEC2, 	GL_FLOAT_VEC3, 	GL_FLOAT_VEC4, 	

    if (type == GL_FLOAT || type == GL_FLOAT_VEC2 || type == GL_FLOAT_VEC3  || type==GL_FLOAT_VEC4 )
    {
        typeName = "float";
        g.glGetUniformfv(program->programId(), id,  fparams);
        value = QString::number(double(fparams[0]));
    }

    if (type == GL_FLOAT_VEC2 || type == GL_FLOAT_VEC3  || type==GL_FLOAT_VEC4 )
    {
        typeName = "vec2";
        value += ", ";
        value += QString::number(double(fparams[1]));
    }

    if (type == GL_FLOAT_VEC3  || type==GL_FLOAT_VEC4 )
    {
        typeName = "vec3";
        value += ", ";
        value += QString::number(double(fparams[2]));
    }

    if (type == GL_FLOAT_VEC4 )
    {
        typeName = "vec4";

        value += ", ";
        value += QString::number(double(fparams[3]));
    }

    // GL_INT, 	GL_INT_VEC2,	GL_INT_VEC3,	GL_INT_VEC4,

    if (type == GL_INT || type == GL_INT_VEC2 || type == GL_INT_VEC3  || type==GL_INT_VEC4 )
    {
        typeName = "int";

        g.glGetUniformiv(program->programId(), id,  iparams);
        value = QString::number(int(iparams[0]));
    }

    if (type == GL_INT_VEC2 || type == GL_INT_VEC3  || type==GL_INT_VEC4 )
    {
        typeName = "ivec2";

        value += ", ";
        value += QString::number(double(iparams[1]));
    }

    if (type == GL_INT_VEC3  || type==GL_INT_VEC4 )
    {
        typeName = "ivec3";
        value += ", ";
        value += QString::number(double(iparams[2]));
    }

    if (type == GL_INT_VEC4 )
    {
        typeName = "ivec4";

        value += ", ";
        value += QString::number(double(iparams[3]));
    }

    // GL_BOOL, 	GL_BOOL_VEC2, 	GL_BOOL_VEC3, 	GL_BOOL_VEC4, 	
    if (type == GL_BOOL || type == GL_BOOL_VEC2 || type == GL_BOOL_VEC3 || type == GL_BOOL_VEC4) 
    {
        typeName = "bool";

        g.glGetUniformiv(program->programId(), id,  iparams);
        if (iparams[0] == 0) value = QString("false");
        else value = QString("true");
    }
    if (type == GL_BOOL_VEC2 || type == GL_BOOL_VEC3 || type == GL_BOOL_VEC4) 
    {
        typeName = "bvec2";

        value += ", ";
        if (iparams[1] == 0) value += QString("false");
        else value += QString("true");
    }
    if (type == GL_BOOL_VEC3 || type == GL_BOOL_VEC4) 
    {
        typeName = "bvec3";
        value += ", ";
        if (iparams[2] == 0) value += QString("false");
        else value += QString("true");
    }
    if (type == GL_BOOL_VEC4) 
    {
        typeName = "bvec4";
        value += ", ";
        if (iparams[3] == 0) value += QString("false");
        else value += QString("true");
    }

    // GL_FLOAT_MAT2, 	GL_FLOAT_MAT3, 	GL_FLOAT_MAT4, 	
    if (type == GL_FLOAT_MAT2) 
    {
        typeName = "mat2";
        g.glGetUniformfv(program->programId(), id,  fparams);
        value = QString::number(double(fparams[0]));
        value += ", ";
        value += QString::number(double(fparams[2]));
        value += "; ";
        value += QString::number(double(fparams[1]));
        value += ", ";
        value += QString::number(double(fparams[3]));        
    }
    if (type == GL_FLOAT_MAT3) 
    {
        typeName = "mat3";
        g.glGetUniformfv(program->programId(), id,  fparams);

        value = QString::number(double(fparams[0]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[3]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[6]),'g',3);

        value += "; ";

        value += QString::number(double(fparams[1]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[4]),'g',3);        
        value += ", ";
        value += QString::number(double(fparams[7]),'g',3);

        value += "; ";

        value += QString::number(double(fparams[2]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[5]),'g',3);        
        value += ", ";
        value += QString::number(double(fparams[8]),'g',3);

    }

   if (type == GL_FLOAT_MAT4) 
    {
        
        typeName = "mat4";
        g.glGetUniformfv(program->programId(), id,  fparams);
        
        value = QString::number(double(fparams[0]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[4]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[8]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[12]),'g',3);

        value += "; ";

        value += QString::number(double(fparams[1]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[5]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[9]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[13]),'g',3);

        value += "; ";

        value += QString::number(double(fparams[2]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[6]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[10]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[14]),'g',3);

        value += "; ";

        value += QString::number(double(fparams[3]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[7]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[11]),'g',3);
        value += ", ";
        value += QString::number(double(fparams[15]),'g',3);
    }

    // GL_SAMPLER_2D, or GL_SAMPLER_CUBE

    if (type == GL_SAMPLER_2D) 
    {
        typeName = "sampler2D";
        g.glGetUniformiv(program->programId(), id,  iparams);
        value = QString::number(int(iparams[0]));
    }

    if (type == GL_SAMPLER_CUBE) 
    {
        typeName = "samplerCube";
        g.glGetUniformiv(program->programId(), id,  iparams);
        value = QString::number(int(iparams[0]));
    }
}

void ShaderLoader::uniformMult(bool up)
{
    GLWidget& g = *glwidget();  
    int id = activeUniform;
    if (id == -1) return;    
    if (!program) return;
    program->bind();

    GLchar name[500];
    GLsizei length;
    GLint size;
    GLenum type;
    g.glGetActiveUniform (program->programId(), id, 500, &length, &size, &type, &name[0]);

    GLint MAX;
    g.glGetProgramiv(program->programId(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &MAX);
    GLint iparams[MAX];
    GLfloat fparams[MAX];

    // 	GL_FLOAT, 	GL_FLOAT_VEC2, 	GL_FLOAT_VEC3, 	GL_FLOAT_VEC4, 	
    if (type == GL_FLOAT)
    {        
        g.glGetUniformfv(program->programId(), id,  fparams);
        float value = fparams[0];
        if (up) value *= 2.0;
        else value /= 2.0;
        program->setUniformValue(name, value);
    }

    if (type == GL_INT)
    {        
        g.glGetUniformiv(program->programId(), id,  iparams);
        int value = iparams[0];
        if (up) value+=1;
        else value-=1;
        program->setUniformValue(name, value);
    }
}


void ShaderLoader::showMenu(const QPoint& pos)
{
    GLWidget& g = *glwidget();
    g.makeCurrent();
    
    timer.stop();


    // 1. Actions

    // Info
    vector<QAction*> info; 
    info.push_back(new QAction(QString("Current path is ") + QDir::currentPath() , glwidget()));
    if (filename!="")
    {
        // VS
        // if (!enabled_vs) g.glColor3f(0.5, 0.5, 0.5);
        // else if (vs && vs->isCompiled()) g.glColor3f(0.0, 0.5, 0.0); 
        // else g.glColor3f(0.5, 0.0, 0.0);
        QString aux("VS: "+filename+".vert ");
        if (!enabled_vs) aux+=QString("[DISABLED]");
        else
        {
            if (vs && vs->isCompiled()) aux+=QString("[COMPILE: OK]");
            else aux+=QString("[COMPILE: ERROR]");
        }

        info.push_back(new QAction(aux  , glwidget()));

        // GS
        // if (!enabled_gs) g.glColor3f(0.5, 0.5, 0.5);
        // else if (gs && gs->isCompiled()) g.glColor3f(0.0, 0.5, 0.0); 
        // else g.glColor3f(0.5, 0.0, 0.0);
        aux=QString("GS: "+filename+".geom ");
        if (!enabled_gs) aux+=QString("[DISABLED]");
        else
        {
            if (gs && gs->isCompiled()) aux+=QString("[COMPILE: OK]");
            else aux+=QString("[COMPILE: ERROR]");
        }
        info.push_back(new QAction(aux  , glwidget()));

        // FS
        // if (!enabled_fs) g.glColor3f(0.5, 0.5, 0.5);
        // else if (fs && fs->isCompiled()) g.glColor3f(0.0, 0.5, 0.0); 
        // else g.glColor3f(0.5, 0.0, 0.0);
        aux=QString("FS: "+filename+".frag ");
        if (!enabled_fs) aux+=QString("[DISABLED]");
        else
        {
            if (fs && fs->isCompiled()) aux+=QString("[COMPILE: OK]");
            else aux+=QString("[COMPILE: ERROR]");
        }
        info.push_back(new QAction(aux  , glwidget()));

        // PROGRAM
        if (program)
        {
            if (program->isLinked())
            {
                // g.glColor3f(0.0, 0.5, 0.0); 
                info.push_back(new QAction(QString("PROGRAM LINK: OK") , glwidget()));
            }
            else
            {
                // g.glColor3f(0.5, 0.0, 0.0); 
                info.push_back(new QAction(QString("PROGRAM LINK: ERROR") , glwidget()));
            }
        }   
    }
    else
        info.push_back(new QAction(QString("No shaders loaded") , glwidget()));

    // Shaders 
    QAction* actionNewVSFS = new QAction("New VS+FS...", glwidget());
    //actionNew->setShortcut(QString("Ctrl+N"));
    connect(actionNewVSFS, SIGNAL(triggered()), this, SLOT(createDefaultShadersVSFS()));

    QAction* actionNewVSGSFS = new QAction("New VS+GS+FS...", glwidget());
    //actionNew->setShortcut(QString("Ctrl+N"));
    connect(actionNewVSGSFS, SIGNAL(triggered()), this, SLOT(createDefaultShadersVSGSFS()));

    QAction* actionCreateFromTemplate = new QAction("New (from existing shaders)...", glwidget());
    connect(actionCreateFromTemplate, SIGNAL(triggered()), this, SLOT(createShaderFromTemplate()));


    QAction* actionOpen = new QAction("Open shaders...", glwidget());
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(attachShaders()));

    QAction* actionVS = new QAction("Vertex shader", glwidget());
    actionVS->setCheckable(true);
    actionVS->setChecked(enabled_vs);
    connect(actionVS, SIGNAL(toggled(bool)), this, SLOT(switchStatusVS()));

    QAction* actionGS = new QAction("Geometry shader", glwidget());
    actionGS->setCheckable(true);
    actionGS->setChecked(enabled_gs);
    connect(actionGS, SIGNAL(toggled(bool)), this, SLOT(switchStatusGS()));

    QAction* actionFS = new QAction("Fragment shader", glwidget());
    actionFS->setCheckable(true);
    actionFS->setChecked(enabled_fs);
    connect(actionFS, SIGNAL(toggled(bool)), this, SLOT(switchStatusFS()));

    QAction* actionRunTest = new QAction("Run test", glwidget());
    connect(actionRunTest, SIGNAL(triggered()), this, SLOT(compareTest()));


    // Scene
    QAction* actionAddObject = new QAction("Add object...", glwidget());
    connect(actionAddObject, SIGNAL(triggered()), glwidget(), SLOT(addObject()));

    QAction* actionLoadObject = new QAction("Load object...", glwidget());
    connect(actionLoadObject, SIGNAL(triggered()), this, SLOT(loadObject()));

    QAction* actionClearScene = new QAction("Clear scene", glwidget());
    connect(actionClearScene, SIGNAL(triggered()), glwidget(), SLOT(clearScene()));



    // Render options
    QAction* actionWireframe = new QAction("Wireframe rendering", glwidget());
    actionWireframe->setCheckable(true);
    actionWireframe->setChecked(wireframe);
    connect(actionWireframe, SIGNAL(toggled(bool)), this, SLOT(switchStatusWireframe()));

    QAction* actionShowAxes = new QAction("Show Axes", glwidget());
    actionShowAxes->setCheckable(true);
    actionShowAxes->setChecked(showAxes);
    connect(actionShowAxes, SIGNAL(toggled(bool)), this, SLOT(switchStatusShowAxes()));

    QAction* actionShowLight = new QAction("Show Light", glwidget());
    actionShowLight->setCheckable(true);
    actionShowLight->setChecked(showLight);
    connect(actionShowLight, SIGNAL(toggled(bool)), this, SLOT(switchStatusShowLight()));

    QAction* actionBackground = new QAction("Background color", glwidget());
    connect(actionBackground, SIGNAL(triggered()), this, SLOT(changeBackgroundColor()));

    // Camera
    QAction* actionResetCamera = new QAction("Reset camera", glwidget());
    connect(actionResetCamera, SIGNAL(triggered()), this, SLOT(resetCamera()));

    QAction* actionCameraPreset1 = new QAction("Preset 1", glwidget());
    connect(actionCameraPreset1, SIGNAL(triggered()), this, SLOT(cameraPreset1()));

    QAction* actionCameraPreset2 = new QAction("Preset 2", glwidget());
    connect(actionCameraPreset2, SIGNAL(triggered()), this, SLOT(cameraPreset2()));

    QAction* actionCameraPreset3 = new QAction("Preset 3", glwidget());
    connect(actionCameraPreset3, SIGNAL(triggered()), this, SLOT(cameraPreset3()));

    QAction* actionCameraPreset4 = new QAction("Preset 4", glwidget());
    connect(actionCameraPreset4, SIGNAL(triggered()), this, SLOT(cameraPreset4()));

    QAction* actionCameraPreset5 = new QAction("Preset 5", glwidget());
    connect(actionCameraPreset5, SIGNAL(triggered()), this, SLOT(cameraPreset5()));

    // Textures
    QAction* actionLoadTexture0 = new QAction("Load image for texture unit 0", glwidget());
    connect(actionLoadTexture0, SIGNAL(triggered()), this, SLOT(loadTexture0()));

    QAction* actionLoadTexture1 = new QAction("Load image for texture unit 1", glwidget());
    connect(actionLoadTexture1, SIGNAL(triggered()), this, SLOT(loadTexture1()));

    QAction* actionLoadTexture2 = new QAction("Load image for texture unit 2", glwidget());
    connect(actionLoadTexture2, SIGNAL(triggered()), this, SLOT(loadTexture2()));

    QAction* actionLoadTexture3 = new QAction("Load image for texture unit 3", glwidget());
    connect(actionLoadTexture3, SIGNAL(triggered()), this, SLOT(loadTexture3()));

    QAction* actionShowTextures = new QAction("Show textures (external viewer)", glwidget());
    connect(actionShowTextures, SIGNAL(triggered()), this, SLOT(showTextures()));


    // Lights
    QAction* actionLightAmbient = new QAction("Set ambient color...", glwidget());
    connect(actionLightAmbient, SIGNAL(triggered()), this, SLOT(setLightAmbient()));

    QAction* actionLightDiffuse = new QAction("Set diffuse color...", glwidget());
    connect(actionLightDiffuse, SIGNAL(triggered()), this, SLOT(setLightDiffuse()));

    QAction* actionLightSpecular = new QAction("Set specular color...", glwidget());
    connect(actionLightSpecular, SIGNAL(triggered()), this, SLOT(setLightSpecular()));

    QAction* actionLightSetPosWorld = new QAction("Set light position in World Space...", glwidget());
    connect(actionLightSetPosWorld, SIGNAL(triggered()), this, SLOT(setLightPositionWorld()));

    QAction* actionLightSetPosEye = new QAction("Set light position in Eye Space...", glwidget());
    connect(actionLightSetPosEye, SIGNAL(triggered()), this, SLOT(setLightPositionEye()));

    QAction* actionLightResetPos = new QAction("Reset light position (eye space origin)", glwidget());
    connect(actionLightResetPos, SIGNAL(triggered()), this, SLOT(resetLightPosition()));

    QAction* actionLightRotate = new QAction("Auto-rotate light", glwidget());
    connect(actionLightRotate, SIGNAL(triggered()), this, SLOT(switchLightRotate()));
    actionLightRotate->setCheckable(true);
    actionLightRotate->setChecked(lightRotate);


    // Material
    QAction* actionMaterialAmbient = new QAction("Set ambient color...", glwidget());
    connect(actionMaterialAmbient, SIGNAL(triggered()), this, SLOT(setMaterialAmbient()));

    QAction* actionMaterialDiffuse = new QAction("Set diffuse color...", glwidget());
    connect(actionMaterialDiffuse, SIGNAL(triggered()), this, SLOT(setMaterialDiffuse()));

    QAction* actionMaterialSpecular = new QAction("Set specular color...", glwidget());
    connect(actionMaterialSpecular, SIGNAL(triggered()), this, SLOT(setMaterialSpecular()));

    // User Uniforms
    vector<QAction*> actionUniforms;
    if (program && program->isLinked())
    {
        GLint count;
        g.glGetProgramiv (program->programId(), GL_ACTIVE_UNIFORMS, &count);
        for (int i=0; i<count; ++i)
        {
            GLchar name[500];
            GLsizei length;
            GLint size;
            GLenum type;
            g.glGetActiveUniform (program->programId(), i, 500, &length, &size, &type, &name[0]);
            //cout << i << " " << name << " Size: " << size << " Type: " << type << endl;
            if (isPredefinedUniform(name)) continue; 
            // 	GL_FLOAT, 	GL_FLOAT_VEC2, 	GL_FLOAT_VEC3, 	GL_FLOAT_VEC4, 	GL_INT, 	GL_INT_VEC2,	GL_INT_VEC3,	GL_INT_VEC4,
	        // GL_BOOL, 	GL_BOOL_VEC2, 	GL_BOOL_VEC3, 	GL_BOOL_VEC4, 	GL_FLOAT_MAT2, 	GL_FLOAT_MAT3, 	GL_FLOAT_MAT4, 	GL_SAMPLER_2D, or
	        // GL_SAMPLER_CUBE

            QString value, typeName; 
            uniformValueToString(i, value, typeName);
           
            QAction* tmp;

            if (type == GL_BOOL)
            {
                tmp = new QAction(QString("")+typeName + " " + QString(name) + QString(" = ") + value + QString(" [switch]"), glwidget());
            }
            else
            {
                if (type == GL_FLOAT || type == GL_INT)
                    tmp = new QAction(QString("")+ typeName + " " + QString(name) + QString(" = ") + value + QString(" [edit...]"), glwidget());
                else
                    tmp = new QAction(QString("")+ typeName + " " + QString(name) + QString(" = ") + value + QString(""), glwidget());
            }
            if (type == GL_BOOL || type == GL_FLOAT || type == GL_INT)
            {
                tmp->setData(QVariant(ID_OFFSET+i));  // uniform id
                tmp->setCheckable(true);
            }
            else 
                tmp->setData(QVariant(0));  // uniform id

            if (activeUniform == i) tmp->setChecked(true);

            actionUniforms.push_back(tmp); 
        }
    }    

    // User Uniforms
    vector<QAction*> actionSystemUniforms;
    if (program && program->isLinked())
    {
        GLint count;
        g.glGetProgramiv (program->programId(), GL_ACTIVE_UNIFORMS, &count);
        for (int i=0; i<count; ++i)
        {
            GLchar name[500];
            GLsizei length;
            GLint size;
            GLenum type;
            g.glGetActiveUniform (program->programId(), i, 500, &length, &size, &type, &name[0]);
            //cout << i << " " << name << " Size: " << size << " Type: " << type << endl;
            if (!isPredefinedUniform(name)) continue; 

            QString value, typeName; 
            uniformValueToString(i, value, typeName);
           
            QAction* tmp;

            tmp = new QAction(QString("")+typeName + " " + QString(name) + QString(" = ") + value, glwidget());
            tmp->setData(QVariant(0));  // uniform id
            tmp->setCheckable(false);

            actionSystemUniforms.push_back(tmp); 
        }
    }    




    QMenu menu(glwidget());

    QMenu* infos = menu.addMenu("Info");
    for (unsigned int i=0; i<info.size(); ++i)
        infos->addAction(info[i]);

    QMenu* shaders = menu.addMenu("Shaders");
    shaders->addAction(actionNewVSFS);
    shaders->addAction(actionNewVSGSFS);
    shaders->addAction(actionCreateFromTemplate);
    shaders->addSeparator();
    shaders->addAction(actionOpen);
    shaders->addSeparator();
    shaders->addAction(actionVS);
    shaders->addAction(actionGS);
    shaders->addAction(actionFS);
    shaders->addSeparator();
    shaders->addAction(actionRunTest);


    QMenu* scene = menu.addMenu("Scene");
    scene->addAction(actionClearScene);
    scene->addAction(actionLoadObject);
    scene->addAction(actionAddObject);




    QMenu* render = menu.addMenu("Render options");
    render->addAction(actionWireframe);
    render->addAction(actionShowAxes);
    render->addAction(actionShowLight);
    render->addSeparator();
    render->addAction(actionBackground);

    QMenu* cameraMenu = menu.addMenu("Camera");
    cameraMenu->addAction(actionResetCamera);
    cameraMenu->addSeparator();
    cameraMenu->addAction(actionCameraPreset1);
    cameraMenu->addAction(actionCameraPreset2);
    cameraMenu->addAction(actionCameraPreset3);
    cameraMenu->addAction(actionCameraPreset4);
    cameraMenu->addAction(actionCameraPreset5);

    QMenu* textures = menu.addMenu("Textures");
    textures->addAction(actionLoadTexture0);
    textures->addAction(actionLoadTexture1);
    textures->addAction(actionLoadTexture2);
    textures->addAction(actionLoadTexture3);
    textures->addSeparator();
    textures->addAction(actionShowTextures);

    QMenu* lights = menu.addMenu("Lights");
    lights->addAction(actionLightAmbient);
    lights->addAction(actionLightDiffuse);
    lights->addAction(actionLightSpecular);
    lights->addSeparator();
    lights->addAction(actionLightSetPosWorld);
    lights->addAction(actionLightSetPosEye);
    lights->addSeparator();
    lights->addAction(actionLightRotate);
    lights->addSeparator();
    lights->addAction(actionLightResetPos);

    QMenu* materials = menu.addMenu("Material");
    materials->addAction(actionMaterialAmbient);
    materials->addAction(actionMaterialDiffuse);
    materials->addAction(actionMaterialSpecular);

    QMenu* uniforms = menu.addMenu("Uniforms");
    for (unsigned int i=0; i<actionUniforms.size(); ++i)
        uniforms->addAction(actionUniforms[i]);
    uniforms->addSeparator();
    for (unsigned int i=0; i<actionSystemUniforms.size(); ++i)
        uniforms->addAction(actionSystemUniforms[i]);


    QAction* action = menu.exec(pos);
    g.makeCurrent();

    if (action && action->data().toInt() > 0)
    {
        // uniform edit
        int id = action->data().toInt() - ID_OFFSET; 
        editUniform(id);
    }
    
    timer.start(); 
    //CHECK();
}

void ShaderLoader::loadObject()
{
    glwidget()->clearScene();
    glwidget()->addObject();
}

void ShaderLoader::loadObject(const QString& file)
{
    glwidget()->clearScene();
    glwidget()->addObjectFromFile(file);
}

void ShaderLoader::editUniform(int id)
{
    GLWidget& g = *glwidget();
    //timer.start(); // experimental 

    if (!program) return;
    program->bind();

    GLchar name[500];
    GLsizei length;
    GLint size;
    GLenum type;
    g.glGetActiveUniform (program->programId(), id, 500, &length, &size, &type, &name[0]);

    GLint MAX;
    g.glGetProgramiv(program->programId(), GL_ACTIVE_UNIFORM_MAX_LENGTH, &MAX);
    GLint iparams[MAX];
    GLfloat fparams[MAX];

    // 	GL_FLOAT, 	GL_FLOAT_VEC2, 	GL_FLOAT_VEC3, 	GL_FLOAT_VEC4, 	
    if (type == GL_FLOAT)
    {        
        g.glGetUniformfv(program->programId(), id,  fparams);
        float value = fparams[0];
        bool active = true;
        CustomDialog d("Edit uniform "+QString(name), glwidget());
        d.addLabel    ("Enter new value for \""+QString(name)+QString("\""));
        d.addCheckBox ("Active uniform (edit with UP/DOWN keys)", &active);
        d.addDblSpinBoxF("Value: ", -1e10, 1e10, &value, 2, 1);
        d.exec(); 
	g.makeCurrent();
	
        if (!d.wasCancelled()) 
        {
            program->bind(); // bind again because the dialog may caused the program to be released
            program->setUniformValue(name, value);
            if (active) activeUniform = id; 
        }
    }



     // GL_INT, 	GL_INT_VEC2,	GL_INT_VEC3,	GL_INT_VEC4,
    if (type == GL_INT )
    {        
        g.glGetUniformiv(program->programId(), id,  iparams);
        int value = iparams[0];
        bool active = true;
        CustomDialog d("Edit uniform "+QString(name), glwidget());
        d.addLabel    ("Enter new value for \""+QString(name)+QString("\""));
        d.addCheckBox ("Active uniform (edit with UP/DOWN keys)", &active);
        d.addSpinBox("Value: ", -100000, 100000, &value, 1);
        d.exec(); 
        g.makeCurrent();
	
        if (!d.wasCancelled()) 
        {
            program->bind(); // bind again because the dialog may caused the program to be released
            program->setUniformValue(name, value);
            if (active) activeUniform = id; 
        }
    }

	        // GL_BOOL, 	GL_BOOL_VEC2, 	GL_BOOL_VEC3, 	GL_BOOL_VEC4, 	GL_FLOAT_MAT2, 	GL_FLOAT_MAT3, 	GL_FLOAT_MAT4, 	
        // GL_SAMPLER_2D, or GL_SAMPLER_CUBE

    if (type == GL_BOOL)
    {
        g.glGetUniformiv(program->programId(), id,  iparams);
        //cout << "Name:" << name << endl;
        if (iparams[0] == 0) program->setUniformValue(name, true);
        else program->setUniformValue(name, false);
    }
    
    program->release();
}

void ShaderLoader::loadTexture(int unit, QString filename)
{
  GLWidget& g = *glwidget();
  g.makeCurrent();
    QString textures = "/assig/grau-g/Textures";
    char* tmp = getenv ("VTEXTURES");
    if (tmp!=NULL) textures=QString(tmp);

    // delete previous texture, if any
    if (textureID[unit])
        g.glDeleteTextures(1, &(textureID[unit]));

    if (filename.size()==0)
	    filename = QFileDialog::getOpenFileName(0, "Open Image", textures, "Image file (*.png *.jpg)");	
    
	QImage img1(filename);	
    if (img1.isNull())
    {
      QImage img1std(textures+QString("/")+QFileInfo(filename).fileName());
      if (img1std.isNull()){
        cout << "Couldn't load image " << endl;
        return;
      }
      img1 = img1std;
    }
    textureName[unit]=filename;
	QImage im0 = img1.convertToFormat(QImage::Format_ARGB32).rgbSwapped().mirrored();
	g.glGenTextures( 1, &(textureID[unit]));
	g.glBindTexture(GL_TEXTURE_2D, textureID[unit]);
	g.glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, im0.width(), im0.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, im0.bits());
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	g.glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	g.glBindTexture(GL_TEXTURE_2D, 0);
    //CHECK();
	g.glActiveTexture(GL_TEXTURE0);
}

void ShaderLoader::loadTexture0()
{
  loadTexture(0, "");
}

void ShaderLoader::loadTexture1()
{
  loadTexture(1, "");
}

void ShaderLoader::loadTexture2()
{
  loadTexture(2, "");
}

void ShaderLoader::loadTexture3()
{
  loadTexture(3, "");
}

void ShaderLoader::switchStatusVS()
{
    enabled_vs = !enabled_vs;
    reloadShaders();
}

void ShaderLoader::switchStatusGS()
{
    enabled_gs = !enabled_gs;
    reloadShaders();
}
void ShaderLoader::switchStatusFS()
{
    enabled_fs = !enabled_fs;
    reloadShaders();
}

void ShaderLoader::switchStatusWireframe()
{
    wireframe = !wireframe;
    glwidget()->update();
    //glwidget()->updateGL();
}

void ShaderLoader::switchStatusShowAxes()
{
    showAxes = !showAxes;
    glwidget()->update();
    //glwidget()->updateGL();
}

void ShaderLoader::switchStatusShowLight()
{
    showLight = !showLight;
    glwidget()->update();
    //glwidget()->updateGL();
}

void ShaderLoader::resetCamera()
{
    camera()->init(scene()->boundingBox());
    glwidget()->update();
    //glwidget()->updateGL();
}

void ShaderLoader::cameraPreset1()
{
    camera()->init(scene()->boundingBox());
    camera()->incrementAngleX(45);
    glwidget()->update();
}

void ShaderLoader::cameraPreset2()
{
    camera()->init(scene()->boundingBox());
    camera()->incrementAngleX(45);
    camera()->incrementAngleY(45);
    glwidget()->update();
}

void ShaderLoader::cameraPreset3()
{
    camera()->init(scene()->boundingBox());
    camera()->incrementAngleX(45);
    camera()->incrementAngleY(180);
    glwidget()->update();
}

void ShaderLoader::cameraPreset4()
{
    camera()->init(scene()->boundingBox());
    camera()->incrementAngleX(45);
    camera()->incrementAngleY(45);
    camera()->incrementDistance(scene()->boundingBox().radius());
    camera()->updateClippingPlanes(scene()->boundingBox());
    glwidget()->update();
}
void ShaderLoader::cameraPreset5()
{
    camera()->init(scene()->boundingBox());
    camera()->incrementAngleX(45);
    camera()->incrementAngleY(45);
    camera()->incrementDistance(10*scene()->boundingBox().radius());
    camera()->updateClippingPlanes(scene()->boundingBox());
    glwidget()->update();
}

QColor v2c(const Vector& v)
{
    return QColor(255*v.x(), 255*v.y(), 255*v.z());
}

void ShaderLoader::changeBackgroundColor()
{
    QColor color = QColorDialog::getColor(v2c(backgroundColor));
    backgroundColor = Vector(color.redF(), color.greenF(), color.blueF());
}

void ShaderLoader::setLightAmbient()
{
    QColor color = QColorDialog::getColor(v2c(lightAmbient));
    lightAmbient = Vector(color.redF(), color.greenF(), color.blueF());
}

void ShaderLoader::setLightDiffuse()
{
    QColor color = QColorDialog::getColor(v2c(lightDiffuse));
    lightDiffuse = Vector(color.redF(), color.greenF(), color.blueF());
}

void ShaderLoader::setLightSpecular()
{
    QColor color = QColorDialog::getColor(v2c(lightSpecular));
    lightSpecular = Vector(color.redF(), color.greenF(), color.blueF());
}

void ShaderLoader::setLightPositionEye()
{
    bool ok;

    double x = QInputDialog::getDouble(glwidget(), "Light position (eye space):", "X:", lightPosition.x(), -100000, 100000, 2, &ok);
    if (!ok) return;

    double y = QInputDialog::getDouble(glwidget(), "Light position (eye space):", "Y:", lightPosition.y(), -100000, 100000, 2, &ok);
    if (!ok) return;

    double z = QInputDialog::getDouble(glwidget(), "Light position (eye space):", "Z:", lightPosition.z(), -100000, 100000, 2, &ok);
    if (!ok) return;

    lightEncodedInEyeSpace = true;
    lightRotate = false;
    lightPosition = QVector4D(x,y,z,1.0);
    glwidget()->makeCurrent();
}

void ShaderLoader::setLightPositionWorld()
{
    bool ok;

    double x = QInputDialog::getDouble(glwidget(), "Light position (world space):", "X:", lightPosition.x(), -100000, 100000, 2, &ok);
    if (!ok) return;

    double y = QInputDialog::getDouble(glwidget(), "Light position (world space):", "Y:", lightPosition.y(), -100000, 100000, 2, &ok);
    if (!ok) return;

    double z = QInputDialog::getDouble(glwidget(), "Light position (world space):", "Z:", lightPosition.z(), -100000, 100000, 2, &ok);
    if (!ok) return;

    lightEncodedInEyeSpace = false;
    lightRotate = false;
    lightPosition = QVector4D(x,y,z,1.0);
    glwidget()->makeCurrent();
}

void ShaderLoader::resetLightPosition()
{
    lightRotate = false;
    lightEncodedInEyeSpace = true;
    lightPosition = QVector4D(0,0,0,1);
}

void ShaderLoader::switchLightRotate()
{
    if (lightRotate)
    {
        resetLightPosition();
        lightRotate = false;   
    }
    else
    {
        lightEncodedInEyeSpace = false;
        lightRotate = true;
    }
}

void ShaderLoader::setMaterialAmbient()
{
    QColor color = QColorDialog::getColor(v2c(materialAmbient));
    materialAmbient = Vector(color.redF(), color.greenF(), color.blueF());
    glwidget()->makeCurrent();    
}

void ShaderLoader::setMaterialDiffuse()
{
    QColor color = QColorDialog::getColor(v2c(materialDiffuse));
    materialDiffuse = Vector(color.redF(), color.greenF(), color.blueF());
    glwidget()->makeCurrent();
}

void ShaderLoader::setMaterialSpecular()
{
    QColor color = QColorDialog::getColor(v2c(materialSpecular));
    materialSpecular = Vector(color.redF(), color.greenF(), color.blueF());
    glwidget()->makeCurrent();
}



void ShaderLoader::reloadShaders()
{
    QString title;
    glwidget()->makeCurrent();
    //cout << "The shaders have been reloaded" << endl;
    QString name=filename;
    if (name=="") return;
    //if (!enabled_vs && !enabled_gs && !enabled_fs) return;

    // clean up
    if (vs) delete vs;
    if (gs) delete gs;
    if (fs) delete fs;
    if (program) delete program;
    vs=gs=fs=0;
    program=0;
    enabled_vs = enabled_gs = enabled_fs = true; 
    // VS
    if (enabled_vs)
    {
        if (QFile::exists(name+".vert"))
        {
            QFileInfo fi(name+".vert");
            title+=QString(fi.fileName());
            title+="   ";
            lastModifiedVS = fi.lastModified();

            vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
            vs->compileSourceFile(name+".vert");
            cout << "Compiling VERTEX SHADER " << name.toStdString() << ".vert" << endl;
            if (vs->log().size())            
                qDebug() << vs->log() << endl;
            else
                cout << " compilation OK" << endl;
            if (!vs->isCompiled() and not testMode) {
                QMessageBox::warning(glwidget(), "ShaderLoader", 
                    QString("The Vertex Shader did not compile. \n See log for errors.\n")+vs->log(), QMessageBox::Ok); 
		glwidget()->makeCurrent();
	    }
        }   
        else enabled_vs = false;
    }

    // GS
    if (enabled_gs)
    {
        if (QFile::exists(name+".geom"))
        {
            QFileInfo fi(name+".geom");
            title+=QString(fi.fileName());
            title+="   ";
            lastModifiedGS = fi.lastModified();

            gs = new QOpenGLShader(QOpenGLShader::Geometry, this);
            gs->compileSourceFile(name+".geom");
            cout << "Compiling GEOMETRY SHADER " << name.toStdString() << ".geom" << endl;
            if (gs->log().size())            
                qDebug() << gs->log() << endl;
            else
                cout << " compilation OK" << endl;
            if (!gs->isCompiled() and not testMode) {
                QMessageBox::warning(glwidget(), "ShaderLoader", 
                    QString("The Geometry Shader did not compile. \n"
			    "See log for errors.\n")+gs->log(),
				     QMessageBox::Ok);
		glwidget()->makeCurrent();
	    }
        }
        else enabled_gs = false;
    }
    
    // FS
    if (enabled_fs)
    {
        if (QFile::exists(name+".frag"))
        {
            QFileInfo fi(name+".frag");
            title+=QString(fi.fileName());
            title+="   ";
            lastModifiedFS = fi.lastModified();
            fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
            fs->compileSourceFile(name+".frag");
            cout << "Compiling FRAGMENT SHADER " << name.toStdString() << ".frag" << endl;
            if (fs->log().size())            
                qDebug() << fs->log() << endl;
            else
                qDebug() << " compilation OK" << endl;

            if (!fs->isCompiled() and not testMode) {
                QMessageBox::warning(glwidget(), "ShaderLoader", 
                    QString("The Fragment Shader did not compile. \n"
			    "See log for errors.\n")+fs->log(),
				     QMessageBox::Ok);
		glwidget()->makeCurrent();
	    }
        }
        else enabled_fs = false;
    }

    if (enabled_vs || enabled_gs || enabled_fs)
    {
        program = new QOpenGLShaderProgram(this);
        if (enabled_vs)
            program->addShader(vs);
        if (enabled_gs)
            program->addShader(gs);
        if (enabled_fs)
            program->addShader(fs);
        //qDebug() << "Linking " << endl;
        if (  (!enabled_vs || vs->isCompiled()) &&  (!enabled_fs || fs->isCompiled()) && (!enabled_gs || gs->isCompiled()) )
        {
            program->link();
            if (program->log().size())
                qDebug() << program->log() << endl;
            if (!program->isLinked()) {
                QMessageBox::warning(glwidget(), "ShaderLoader", 
                        QString("The Shader Program did not link. \n"
				"See log for errors."), QMessageBox::Ok);
		glwidget()->makeCurrent();
	    }
        }
        glwidget()->setWindowTitle(title);
    }
/*
void 	setGeometryInputType(GLenum inputType)
void 	setGeometryOutputType(GLenum outputType)
void 	setGeometryOutputVertexCount(int count)
int 	maxGeometryOutputVertices() const
*/
    
    elapsedTimer.start();
}


void ShaderLoader::checkForUpdates()
{
    if (filename=="") return; // no shader attached
    
    bool reload=false;

    if (enabled_vs)
    {
        QFileInfo info(filename+".vert");
        if (info.lastModified() != lastModifiedVS) reload=true;
    }
    if (enabled_gs)
    {
        QFileInfo info(filename+".geom");
        if (info.lastModified() != lastModifiedGS) reload=true;
    }
    if (enabled_fs)
    {
        QFileInfo info(filename+".frag");
        if (info.lastModified() != lastModifiedFS) reload=true;
    }
    if (reload) reloadShaders();
    //DEBUG();
}

void ShaderLoader::attachShaders()
{
    QString name = QFileDialog::getOpenFileName(glwidget(),
            tr("Open Shader"), QDir::currentPath(), tr("Shader Files (*.vert *.geom *.frag)"));
    if (name!="") 
    {
        name.chop(5);
        attachShaders(name);
    }
}

void ShaderLoader::attachShaders(QString name)
{
    filename = name;
    if (filename.endsWith(".vert") || filename.endsWith(".test") || filename.endsWith(".frag") || filename.endsWith(".geom"))
        filename.chop(5);

    reloadShaders();
    if (not grading) openFilesInTextEditor();
}

void ShaderLoader::openFilesInTextEditor()
{
#ifndef __APPLE__
    QString editor = "gedit";
#else
    QString editor = "/Applications/TextEdit.app";
#endif
    char* pPath = getenv ("VEDITOR");
    if (pPath!=NULL)
        editor=QString(pPath);


    QProcess* process = new QProcess(glwidget());
    if (enabled_gs) {
#ifndef __APPLE__
      process->startDetached(editor, QStringList() << filename+".vert" << filename+".geom" << filename+".frag");
#else
      process->startDetached("open", QStringList() << QString("-a")+editor << filename+".vert" << filename+".geom" << filename+".frag");
#endif
    } else {
#ifndef __APPLE__
      process->startDetached(editor, QStringList() << filename+".vert" << filename+".frag");
#else
      process->startDetached("open", QStringList() << QString("-a")+editor << filename+".vert" << filename+".frag");
#endif
    }
}


void ShaderLoader::showTextures()
{
#ifndef __APPLE__
   QString visor = "eog";
#else
   QString visor = "/Applications/Preview.app";
#endif
    char* pPath;
    pPath = getenv ("VIMAGE");
    if (pPath!=NULL)
        visor=QString(pPath);

    QProcess* process = new QProcess(glwidget());
#ifndef __APPLE__
    process->startDetached(visor,  QStringList() << textureName[0] << textureName[1] << textureName[2] << textureName[3]);
#else
    process->startDetached("open", QStringList() << QString("-a")+visor << textureName[0] << textureName[1] << textureName[2] << textureName[3]);
#endif    
}

void ShaderLoader::drawHelp()
{
    GLWidget& g = *glwidget();  
    return ; // rendertext not supported in core profile
    g.glEnable(GL_COLOR_MATERIAL);
    // g.glColor3f(0.2, 0.2, 0.2);
    // int x = 5;
    // int y = 15;

    // path
    //glwidget()->renderText(x,y, QString("Current path is ") + QDir::currentPath() + QString(" - Press SPACE for menu options"));
    // y+=18;
    
    if (filename!="")
    {
        // VS
        // if (!enabled_vs) g.glColor3f(0.5, 0.5, 0.5);
        // else if (vs && vs->isCompiled()) g.glColor3f(0.0, 0.5, 0.0); 
        // else g.glColor3f(0.5, 0.0, 0.0);
        QString aux("VS: "+filename+".vert ");
        if (!enabled_vs) aux+=QString("[DISABLED]");
        else
        {
            if (vs && vs->isCompiled()) aux+=QString("[COMPILE: OK]");
            else aux+=QString("[COMPILE: ERROR]");
        }
        //glwidget()->renderText(x,y, aux); y+=18;

        // GS
        // if (!enabled_gs) g.glColor3f(0.5, 0.5, 0.5);
        // else if (gs && gs->isCompiled()) g.glColor3f(0.0, 0.5, 0.0); 
        // else g.glColor3f(0.5, 0.0, 0.0);
        aux=QString("GS: "+filename+".geom ");
        if (!enabled_gs) aux+=QString("[DISABLED]");
        else
        {
            if (gs && gs->isCompiled()) aux+=QString("[COMPILE: OK]");
            else aux+=QString("[COMPILE: ERROR]");
        }
        //glwidget()->renderText(x,y, aux); y+=18;

        // FS
        // if (!enabled_fs) g.glColor3f(0.5, 0.5, 0.5);
        // else if (fs && fs->isCompiled()) g.glColor3f(0.0, 0.5, 0.0); 
        // else g.glColor3f(0.5, 0.0, 0.0);
        aux=QString("FS: "+filename+".frag ");
        if (!enabled_fs) aux+=QString("[DISABLED]");
        else
        {
            if (fs && fs->isCompiled()) aux+=QString("[COMPILE: OK]");
            else aux+=QString("[COMPILE: ERROR]");
        }
        //glwidget()->renderText(x,y, aux); y+=18;

        // PROGRAM
        if (program)
        {
            if (program->isLinked())
            {
                // g.glColor3f(0.0, 0.5, 0.0); 
                //glwidget()->renderText(x,y, QString("PROGRAM LINK: OK")); y+=18;
            }
            else
            {
                // g.glColor3f(0.5, 0.0, 0.0); 
                //glwidget()->renderText(x,y, QString("PROGRAM LINK: ERROR")); y+=18;
            }
        }   
    }

    // g.glColor3f(0.2, 0.2, 0.2);
    // x=30;
    // y+=30;

    // g.glColor3f(0.5, 0.5, 0.5);

}

bool ShaderLoader::paintGL()
{
    GLWidget& g = *glwidget();
    g.makeCurrent(); // should NOT be needed...
    predefinedUniforms.clear(); // TODO...

    //cout << "ShaderLoader::paintGL()" << endl;
    //CHECK();
    checkForUpdates();

    // Draw scene 
    if (program && !program->isLinked())
        g.glClearColor(1,0,0,1);
    else
        g.glClearColor(backgroundColor.x(), backgroundColor.y(), backgroundColor.z(), 1.0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);


       // TODO: edit light position
        if (lightRotate)
        {
            float t = float(elapsedTimer.elapsed()/1000.0f); 
            float r = .25*scene()->boundingBox().radius();
            float x = cos(3*t)*(3+cos(4*t));
            float y = sin(3*t)*(3+cos(4*t));
            float z = 4*sin(4*t);
            lightPosition = scene()->boundingBox().center() + QVector4D(r*x,r*y,r*z,1);
            //cout << lightPosition.x() << ", " << lightPosition.y() << ", " << lightPosition.z() << endl;
        }
 
    if (showLight) 
    {
        Vector pos = Vector(lightPosition);
        float r = 1.0-backgroundColor.x();
        float g = 1.0-backgroundColor.y();
        float b = 1.0-backgroundColor.z();
        if (lightEncodedInEyeSpace)
        {
            QMatrix4x4 m = camera()->viewMatrix().inverted();
            QVector4D p = m.map(lightPosition);
            pos = Vector(p);
        }
        Box box(pos);
        box.expand(glwidget()->boundingBoxIncludingAxes());
        camera()->updateClippingPlanes(box);
        glwidget()->drawPoint(pos,r,g,b);
    }
        
    if (showAxes) glwidget()->drawAxes();
    if (showHelp) drawHelp();

    // Draw scene
    if (program && program->isLinked()) 
    {
        program->bind();

        program->setUniformValue("time", float(elapsedTimer.elapsed()/1000.0f));
        predefinedUniforms.push_back("time");

        program->setUniformValue("boundingBoxMin", scene()->boundingBox().min());
        predefinedUniforms.push_back("boundingBoxMin");

        program->setUniformValue("boundingBoxMax", scene()->boundingBox().max());
        predefinedUniforms.push_back("boundingBoxMax");

        QPoint p = glwidget()->mapFromGlobal(QCursor::pos());
        program->setUniformValue("mousePosition", QVector2D(float(p.x()),glwidget()->height()-float(p.y())));
        predefinedUniforms.push_back("mousePosition");


        bool invertible;
        camera()->viewMatrix().inverted(&invertible);
        if (!invertible) cout << "ERROR!!!!" << endl;
        camera()->projectionMatrix().inverted(&invertible);
        if (!invertible) cout << "ERROR!!!!" << endl;
        (camera()->projectionMatrix() * camera()->viewMatrix()).inverted(&invertible);
        if (!invertible) cout << "ERROR!!!!" << endl;

        program->setUniformValue("modelMatrix", QMatrix4x4());
        predefinedUniforms.push_back("modelMatrix");
        program->setUniformValue("modelMatrixInverse", QMatrix4x4());
        predefinedUniforms.push_back("modelMatrixInverse");

        program->setUniformValue("viewMatrix", camera()->viewMatrix());
        predefinedUniforms.push_back("viewMatrix");
        program->setUniformValue("viewMatrixInverse", camera()->viewMatrix().inverted());
        predefinedUniforms.push_back("viewMatrixInverse");

        program->setUniformValue("modelViewMatrix", camera()->viewMatrix());
        predefinedUniforms.push_back("modelViewMatrix");
        program->setUniformValue("modelViewMatrixInverse", camera()->viewMatrix().inverted());
        predefinedUniforms.push_back("modelViewMatrixInverse");

        program->setUniformValue("projectionMatrix", camera()->projectionMatrix());
        predefinedUniforms.push_back("projectionMatrix");
        program->setUniformValue("projectionMatrixInverse", camera()->projectionMatrix().inverted());
        predefinedUniforms.push_back("projectionMatrixInverse");

        program->setUniformValue("modelViewProjectionMatrix", camera()->projectionMatrix() * camera()->viewMatrix());
        predefinedUniforms.push_back("modelViewProjectionMatrix");
        program->setUniformValue("modelViewProjectionMatrixInverse", (camera()->projectionMatrix() * camera()->viewMatrix()).inverted());
        predefinedUniforms.push_back("modelViewProjectionMatrixInverse");

        program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
        predefinedUniforms.push_back("normalMatrix");

        program->setUniformValue("matAmbient", QVector4D(materialAmbient,1));
        predefinedUniforms.push_back("matAmbient");
        program->setUniformValue("matDiffuse", QVector4D(materialDiffuse,1));
        predefinedUniforms.push_back("matDiffuse");
        program->setUniformValue("matSpecular", QVector4D(materialSpecular,1));
        predefinedUniforms.push_back("matSpecular");
        program->setUniformValue("matShininess", materialShininess);
        predefinedUniforms.push_back("matShininess");

        program->setUniformValue("lightAmbient", QVector4D(lightAmbient,1));
        predefinedUniforms.push_back("lightAmbient");
        program->setUniformValue("lightDiffuse", QVector4D(lightDiffuse,1));
        predefinedUniforms.push_back("lightDiffuse");
        program->setUniformValue("lightSpecular", QVector4D(lightSpecular,1));
        predefinedUniforms.push_back("lightSpecular");


        if (lightEncodedInEyeSpace)
            program->setUniformValue("lightPosition", lightPosition);
        else
            program->setUniformValue("lightPosition", camera()->viewMatrix().map(lightPosition));

        //if (lightRotate)
          //  program->setUniformValue("lightPosition", camera()->viewMatrix().map(lightPosition));

       
        predefinedUniforms.push_back("lightPosition");
  

        // samplers: last digit in sampler name indicates binding point; no digit -> unit 0
        GLint count;
        g.glGetProgramiv (program->programId(), GL_ACTIVE_UNIFORMS, &count);
        for (int i=0; i<count; ++i)
        {
            GLchar name[500];
            GLsizei length;
            GLint size;
            GLenum type;
            g.glGetActiveUniform (program->programId(), i, 500, &length, &size, &type, &name[0]);

            if (isPredefinedUniform(name)) continue; 
            if (type == GL_SAMPLER_2D) 
            {
                QString lastDigit = QString(name+length-1);
                int value = lastDigit.toInt();
                program->setUniformValue(name, value);
            }
        }    

        // These uniforms should be the last to be set
        if (testMode)
        {
            for (unsigned int i=0; i<testUniformIntNames.size(); ++i)
                program->setUniformValue(testUniformIntNames[i].toStdString().c_str(), testUniformIntValues[i]);
            for (unsigned int i=0; i<testUniformFloatNames.size(); ++i)
                program->setUniformValue(testUniformFloatNames[i].toStdString().c_str(), testUniformFloatValues[i]);
            for (unsigned int i=0; i<testUniformBoolNames.size(); ++i)
                program->setUniformValue(testUniformBoolNames[i].toStdString().c_str(), testUniformBoolValues[i]);

        }       


        for (int i=0; i<4; ++i)    
        {
            g.glActiveTexture(GL_TEXTURE0+i);
	    g.glBindTexture(GL_TEXTURE_2D, textureID[i]);
        }
        g.glActiveTexture(GL_TEXTURE0);
    }
    else    
        glwidget()->defaultProgram()->bind();
   
   //cout << "ShaderLoader::2()" << endl;

    // draw scene
    if (wireframe) g.glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else g.glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    drawPlugin()->drawScene();

    //cout << "ShaderLoader::3()" << endl;


    if (program) program->release();
    else glwidget()->defaultProgram()->release();

    //glBindTexture(GL_TEXTURE_2D, 0);

    //cout << "ShaderLoader::end()" << endl;

    // experimental
    if (!testMode && grading)
    {   
        testMode = true;
        attachShaders(gradeShader.c_str());
        glwidget()->update();
        executeTest();
        exit(0);
    }

    return true;
}

void ShaderLoader::createDefaultShadersVSFS()
{
    ShaderLoader::createDefaultShaders(false);
} 

void ShaderLoader::createDefaultShadersVSGSFS()
{
    ShaderLoader::createDefaultShaders(true);
} 

void ShaderLoader::createShaderFromTemplate() 
{
    // template name
    QString name = QFileDialog::getOpenFileName(glwidget(),
            tr("Open Shader"), QDir::currentPath(), tr("Shader Files (*.vert *.geom *.frag)"));
    if (name=="") return;
    name.chop(5);

    bool ok;
    QString filename = QInputDialog::getText(glwidget(), "New Shaders",
                                         "Base filename:", QLineEdit::Normal,
                                         "myShader", &ok);

    if (!ok || filename.isEmpty()) return;

    // check if files already exist
    if (QFile::exists(filename+".vert") || QFile::exists(filename+".geom") || QFile::exists(filename+".frag") )
    {
        int ret = QMessageBox::warning(glwidget(), tr("ShaderLoader"),
                                tr("One or more files already exist. \n"
                                   "These files will be overwriten with default content."),
                                QMessageBox::Ok | QMessageBox::Cancel,
                                QMessageBox::Ok);

        if (ret!=QMessageBox::Ok) return;
    }

    if (QFile::exists(name+".vert")) 
    {
        enabled_vs = true;
        QFile::copy(name+".vert", filename+".vert");
    }
    else
        enabled_vs = false;

    if (QFile::exists(name+".geom")) 
    {
        enabled_gs = true;
        QFile::copy(name+".geom", filename+".geom");
    }
    else
        enabled_gs = false;

    if (QFile::exists(name+".frag")) 
    {
        enabled_fs = true;
        QFile::copy(name+".frag", filename+".frag");
    }
    else
        enabled_fs = false;


    // Attach shaders
    attachShaders(filename);
}



void ShaderLoader::createDefaultShaders(bool createAlsoGS) 
{
    bool ok;
    QString filename = QInputDialog::getText(glwidget(), "New Shaders",
                                         "Base filename:", QLineEdit::Normal,
                                         "myShader", &ok);

    if (!ok || filename.isEmpty()) return;

    // check if files already exist
    if (QFile::exists(filename+".vert") || QFile::exists(filename+".geom") || QFile::exists(filename+".frag") )
    {
        int ret = QMessageBox::warning(glwidget(), tr("ShaderLoader"),
                                tr("One or more files already exist. \n"
                                   "These files will be overwriten with default content."),
                                QMessageBox::Ok | QMessageBox::Cancel,
                                QMessageBox::Ok);

        if (ret!=QMessageBox::Ok) return;
    }

    // Check if files can be opened
    QFile fileVS(filename+".vert");
    if (!fileVS.open(QFile::WriteOnly | QFile::Truncate)) 
    {
        cout << "Cannot open .vert file for writing" << endl;
        return;
    }

    QFile fileGS(filename+".geom");
    if (createAlsoGS)
    {
        if (!fileGS.open(QFile::WriteOnly | QFile::Truncate)) 
        {
            fileVS.close();
            return;
        }
    }

    QFile fileFS(filename+".frag");
    if (!fileFS.open(QFile::WriteOnly | QFile::Truncate)) 
    {
        fileVS.close();
        if (createAlsoGS) fileGS.close();
        return;
    }

    // Write VS
    if (true)
    {
        QTextStream out(&fileVS);

        out << "#version 330 core" << endl << endl;
        out << "layout (location = 0) in vec3 vertex;" << endl;
        out << "layout (location = 1) in vec3 normal;" << endl;
        out << "layout (location = 2) in vec3 color;" << endl;
        out << "layout (location = 3) in vec2 texCoord;" << endl << endl;

        if (!createAlsoGS)
        {
            out << "out vec4 frontColor;" << endl;
            out << "out vec2 vtexCoord;" << endl << endl;
        }
        else
            out << "out vec4 vfrontColor;" << endl << endl;

        out << "uniform mat4 modelViewProjectionMatrix;" << endl;
        out << "uniform mat3 normalMatrix;" << endl << endl;
        out << "void main()" << endl;
        out << "{" << endl;
        out << "    vec3 N = normalize(normalMatrix * normal);" << endl;
        if (!createAlsoGS)
        {
            out << "    frontColor = vec4(color,1.0) * N.z;" << endl;
            out << "    vtexCoord = texCoord;" << endl;
        }
        else
            out << "    vfrontColor = vec4(color,1.0) * N.z;" << endl;
        out << "    gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);" << endl;
        out << "}" << endl;
        
        fileVS.close();
    }
    // Write GS
    if (createAlsoGS)
    {
        QTextStream out(&fileGS);
        out << "#version 330 core" << endl;
        out << "        " << endl;
        out << "layout(triangles) in;" << endl;
        out << "layout(triangle_strip, max_vertices = 36) out;" << endl;
        out << "" << endl;
        out << "in vec4 vfrontColor[];" << endl;
        out << "out vec4 gfrontColor;" << endl;
        out << "" << endl;
        out << "void main( void )" << endl;
        out << "{" << endl;
        out << "	for( int i = 0 ; i < 3 ; i++ )" << endl;
        out << "	{" << endl;
        out << "		gfrontColor = vfrontColor[i];" << endl;
        out << "		gl_Position = gl_in[i].gl_Position;" << endl;
        out << "		EmitVertex();" << endl;
        out << "	}" << endl;
        out << "    EndPrimitive();" << endl;
        out << "}" << endl;
        fileGS.close();
    }
    // Write FS
    if (true)
    {   
        QTextStream out(&fileFS);
       
        out << "#version 330 core" << endl;
        out << "" << endl;
        if (!createAlsoGS)
            out << "in vec4 frontColor;" << endl;
        else
            out << "in vec4 gfrontColor;" << endl;
        out << "out vec4 fragColor;" << endl;
        out << "" << endl;
        out << "void main()" << endl;
        out << "{" << endl;
        if (!createAlsoGS)
            out << "    fragColor = frontColor;" << endl;
        else
            out << "    fragColor = gfrontColor;" << endl;
        out << "}" << endl;
        fileFS.close();
    }

    enabled_vs = true;
    enabled_gs = createAlsoGS;
    enabled_fs = true;

    // Attach shaders
    attachShaders(filename);
    
}

QImage summaryImage(const QString& filename,  const QString& testFilename, int id)
{
    QString tests = "/assig/grau-g/tests";
    char* tmp = getenv ("VTESTS");
    if (tmp!=NULL) tests=QString(tmp);

    // output image
    QString outName = filename+QString("-out") + QString::number(id) + QString(".png");
    if (!QFile::exists(outName))
    {
        cerr << "Cannot find image file:" << outName.toStdString() << endl;
        return QImage();
    }
    QImage outImage(outName);

    // reference image. Search in testFilename's dir, else in VTESTS dir
    QFileInfo fi(testFilename);
    QString refName;
    if (fi.canonicalPath().isNull())
      refName = QString(tests)+QString("/")+fi.completeBaseName()+
	QString("-out") + QString::number(id) + ".png";
    else
      refName = fi.canonicalPath()+QString("/")+fi.completeBaseName()+
	QString("-out") + QString::number(id) + ".png";
    if (!QFile::exists(refName))
    {
        cerr << "Cannot find image file:" << refName.toStdString() << endl;
        return QImage();
    }
    QImage refImage(refName);

    // size
    if (outImage.size() != refImage.size()) 
    {
        cerr << "The images to compare have different sizes!" << endl;
        return QImage();
    }   
    int w = outImage.width();
    int h = outImage.height();

    //cout << w << ", "<< h << endl;

    // image difference
    QImage diffImage(w,h, QImage::Format_RGB32);
    diffImage.fill(Qt::white);
    QImage diff2Image(w,h, QImage::Format_RGB32);
    diff2Image.fill(Qt::white);

    for (int i=0; i<w; ++i)
    for (int j=0; j<h; ++j)
    {
        QRgb out = outImage.pixel(i,j);
        QRgb ref = refImage.pixel(i,j);
        int r1 = qRed(out);    
        int r2 = qRed(ref);
        int g1 = qGreen(out);    
        int g2 = qGreen(ref);
        int b1 = qBlue(out);    
        int b2 = qBlue(ref);
        int rd =  abs(int(r1-r2));
        int gd =  abs(int(g1-g2));
        int bd =  abs(int(b1-b2));
        QRgb  dif = qRgb(255-rd, 255-gd, 255-bd); 
        diffImage.setPixel(i, j, dif);

        if (rd || gd || bd) 
            diff2Image.setPixel(i, j, qRgb(255,0,0));

    }

    // summary image
    QImage summaryImage(4*w,h, QImage::Format_RGB32);
    summaryImage.fill(Qt::white);
    QPainter painter(&summaryImage);
    painter.drawImage(0,0,outImage);
    painter.drawImage(w,0,refImage);
    painter.drawImage(2*w,0,diffImage);
    painter.drawImage(3*w,0,diff2Image);

    return summaryImage;
}

void ShaderLoader::compareTest()
{
    QString testFileName = executeTest();

    if (testFileName.size()==0) return;
    
    // compare images in current folder with reference images 
    QImage img1 = summaryImage(filename,  testFileName, 1);
    QImage img2 = summaryImage(filename,  testFileName, 2);
    QImage img3 = summaryImage(filename,  testFileName, 3);
    QImage img4 = summaryImage(filename,  testFileName, 4);

    if (img1.isNull() || img2.isNull() || img3.isNull() || img4.isNull() )
    {
        return;
    }

    // collage image (stack vertically)
    const int fontSize = 48;
    int w = img1.width();
    int h = img1.height();

    QImage summaryImage(w,4*h+fontSize, QImage::Format_RGB32);
    summaryImage.fill(Qt::white);
    QPainter painter(&summaryImage);
    painter.drawImage(0,0*h+fontSize,img1);
    painter.drawImage(0,1*h+fontSize,img2);
    painter.drawImage(0,2*h+fontSize,img3);
    painter.drawImage(0,3*h+fontSize,img4);

    QFont font;
    font.setPixelSize(fontSize);
    painter.setFont(font);
    int w2 = w/4;
    painter.drawText(0*w2, 0, w2, fontSize+5, Qt::AlignHCenter, QString("Your output"));
    painter.drawText(1*w2, 0, w2, fontSize+5, Qt::AlignHCenter, QString("Reference"));
    painter.drawText(2*w2, 0, w2, fontSize+5, Qt::AlignHCenter, QString("Difference (abs)"));
    painter.drawText(3*w2, 0, w2, fontSize+5, Qt::AlignHCenter, QString("Different pixels"));

    // save
    QString summaryName = filename + QString("-cmp.png");
    summaryImage.save(summaryName);

    cout << "Summary image saved: " << summaryName.toStdString() << endl;

    QImage scale = summaryImage.scaled(summaryImage.width()/4, summaryImage.height()/4, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    scale.save(filename + QString("-cmp-small.png")); 

    // open in external editor

#ifndef __APPLE__
   QString visor = "eog";
#else
   QString visor = "/Applications/Preview.app";
#endif
   char* pPath;
   pPath = getenv ("VIMAGE");
   if (pPath!=NULL)
       visor=QString(pPath);

    QProcess* process = new QProcess(glwidget());
#ifndef __APPLE__
    process->startDetached(visor,  QStringList() << summaryName);
#else
    process->startDetached("open", QStringList() << QString("-a") << visor << summaryName);
#endif    
}


QString ShaderLoader::executeTest()
{
    GLWidget& g = *glwidget();
    if (!program) 
    {
        cerr << "No shaders!" << endl;
        return QString();
    }
    if (!program->isLinked())
    {
        cerr << "Program not linked!" << endl;
        return QString();
    }

    program->bind();

    // search order: current path, TEST folder, ask
    QString testFilename = filename+".test";
    if (!QFile::exists(testFilename))
    {
        cerr << "Cannot find test file:" << (testFilename).toStdString() << endl;
        QString tests = "/assig/grau-g/tests";
        char* tmp = getenv ("VTESTS");
        if (tmp!=NULL) tests=QString(tmp);

            QFileInfo fi(filename+".vert");
            QString base = fi.baseName();
        
            testFilename = tests + QString("/")+ base + ".test";
            if (!QFile::exists(testFilename))
            {
                cerr << "Cannot find test file:" << (testFilename).toStdString() << endl;
                // ask the user
                testFilename = QFileDialog::getOpenFileName(0, "Open test file", tests, "Test file (*.test)");	
                if (testFilename.size()==0)         return QString();   
            }
    }
        
    ifstream f((testFilename).toStdString().c_str());
    if (!f.is_open())
    {
        cerr << "Cannot open test file " << (testFilename).toStdString() << endl;
        return QString();
    }
    cout << "Running tests in " <<  (testFilename).toStdString() << std::endl;
    testMode = true;
    resetCamera();

    while (!f.eof())
    {
        string s;
        string cmd;
        f >> cmd;
        if (cmd=="clearScene")
        {
            glwidget()->clearScene();
        }
        else if (cmd=="resize")
        {
            int w, h;
            f >> w >> h;
            glwidget()->resize(w,h);
        }
        else if (cmd=="loadObject")
        {
            f >> s;
	    if (!QFile::exists(QString(s.c_str())))
	      {
		QString models = "/assig/grau-g/models";
		char* tmp = getenv ("VMODELS");
		if (tmp!=NULL) models=QString(tmp);
		//cout << "No he pogut obrir " << s << std::endl;
		s = (models+QString("/")+QFileInfo(s.c_str()).fileName()).toStdString();
		//std::cout<<"així que provo amb: " <<s<<std::endl;
	      }
	    loadObject(QString(s.c_str()));
        }
        else if (cmd=="addObject")
        {
            f >> s;
	    if (!QFile::exists(QString(s.c_str())))
	      {
		QString models = "/assig/grau-g/models";
		char* tmp = getenv ("VMODELS");
		if (tmp!=NULL) models=QString(tmp);
		s = (models+QString("/")+QFileInfo(s.c_str()).fileName()).toStdString();
		// std::cout<<"About to open: " <<s<<std::endl;
	      }
            glwidget()->addObjectFromFile(s.c_str());
        }
        else if (cmd=="wire")
        {   
            wireframe = true;
        }
        else if (cmd=="solid")
        {   
            wireframe = false;
        }
        else if (cmd=="axes")
        {   
            showAxes = true;
        }
        else if (cmd=="noaxes")
        {   
            showAxes = false;
        }
        else if (cmd=="clearColor")
        {   
            float r,g,b;
            f >> r >> g >> b;
            backgroundColor = Vector(r,g,b);
        }
        else if (cmd=="resetCamera")
        {   
            resetCamera();
        }
        else if (cmd=="dist")
        {   
            float dist;
            f >> dist;
            camera()->setDistance(dist*scene()->boundingBox().radius());
            camera()->updateClippingPlanes(scene()->boundingBox());
        }
        else if (cmd=="pitch")
        {   
            float angle;
            f >> angle;
            camera()->setAngleX(angle);
        }
        else if (cmd=="yaw")
        {   
            float angle;
            f >> angle;
            camera()->setAngleY(angle);
        }
        else if (cmd=="roll")
        {   
            float angle;
            f >> angle;
            camera()->setAngleZ(angle);
        }
        else if (cmd=="preset1")
        {   
            cameraPreset1();
        }
        else if (cmd=="preset2")
        {   
            cameraPreset2();
        }
        else if (cmd=="preset3")
        {   
            cameraPreset3();
        }
        else if (cmd=="preset4")
        {   
            cameraPreset4();
        }
        else if (cmd=="preset5")
        {   
            cameraPreset5();
        }
        else if (cmd=="unit0")
        {
            f >> s;
            loadTexture(0, s.c_str());
        }
        else if (cmd=="unit1")
        {
            f >> s;
            loadTexture(1, s.c_str());
        }
        else if (cmd=="unit2")
        {
            f >> s;
            loadTexture(2, s.c_str());
        }
        else if (cmd=="unit3")
        {
            f >> s;
            loadTexture(3, s.c_str());
        }
        else if (cmd=="lightAmbient")
        {
            float r,g,b;
            f >> r >> g >> b; 
            lightAmbient = Vector(r,g,b);
        }
        else if (cmd=="lightDiffuse")
        {
            float r,g,b;
            f >> r >> g >> b;
            lightDiffuse = Vector(r,g,b);
        }
        else if (cmd=="lightSpecular")
        {
            float r,g,b;
            f >> r >> g >> b;
            lightSpecular = Vector(r,g,b);
        }
        else if (cmd=="lightPositionEye")
        {
            lightEncodedInEyeSpace = true;
            float x,y,z,w;
            f >> x >> y >> z >> w;
            lightPosition = QVector4D(x,y,z,w);
        }
        else if (cmd=="lightPositionWorld")
        {
            lightEncodedInEyeSpace = false;
            float x,y,z,w;
            f >> x >> y >> z >> w;
            lightPosition = QVector4D(x,y,z,w);
        }
        else if (cmd=="resetLightPosition")
        {
            resetLightPosition();
        }
        else if (cmd=="matAmbient")
        {
            float r,g,b;
            f >> r >> g >> b;
            materialAmbient = Vector(r,g,b);
        }
        else if (cmd=="matDiffuse")
        {
            float r,g,b;
            f >> r >> g >> b;
            materialDiffuse = Vector(r,g,b);
        }
        else if (cmd=="matSpecular")
        {
            float r,g,b;
            f >> r >> g >> b;
            materialSpecular = Vector(r,g,b);
        }    
        else if (cmd=="matShininess")
        {
            f >> materialShininess;
        }    
        else if (cmd=="grab")
        {
            f >> s; 
            glwidget()->update();
            QImage img = g.grabFramebuffer();
            QString name = filename+QString("-out") + s.c_str() + QString(".png");
            img.save(name);
        }     
        else if (cmd=="int")
        {
            int value;
            f >> s >> value;
            testUniformIntNames.push_back(s.c_str());
            testUniformIntValues.push_back(value);
        }
        else if (cmd=="float")
        {
            float value;
            f >> s >> value;
            testUniformFloatNames.push_back(s.c_str());
            testUniformFloatValues.push_back(value);
        }
        else if (cmd=="bool")
        {
            string value;
            f >> s >> value;
            testUniformBoolNames.push_back(s.c_str());
            testUniformBoolValues.push_back((value=="true" || value=="1"));
        }
        else if (cmd=="time")
        {
            float value;
            f >> value;
            testUniformFloatNames.push_back("time");
            testUniformFloatValues.push_back(value);
        }
        else if (cmd=="exit")
        {
            exit(0);
        }
        else if (QString(cmd.c_str()).trimmed()!="")
            cout << "Unrecognized command: " << cmd << endl;

    }
    f.close();
    testMode = false;
    testUniformIntNames.clear();
    testUniformFloatNames.clear();
    testUniformBoolNames.clear();
    testUniformIntValues.clear();
    testUniformFloatValues.clear();
    testUniformBoolValues.clear();
    return testFilename;
}

