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

#include "effectCRT.h"

void EffectCRT::onPluginLoad()
{
    // Carregar shader, compile & link 
    QString vs_src =
      "#version 330 core\n"
      "uniform mat4 modelViewProjectionMatrix;"
      "in vec3 vertex;"
      "in vec3 color;"
      "out vec4 col;"
      "void main() {"
      "  gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);"
      "  col=vec4(color,1.0);"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
      "#version 330 core\n"
      "out vec4 fragColor;"
      "in vec4 col;"
      "uniform int n;"
      "void main() {"
      "  if (mod((gl_FragCoord.y-0.5), float(n)) > 0.0) discard;"
      "  fragColor=col;"
      "}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
}

void EffectCRT::preFrame() 
{
    // bind shader and define uniforms
    program->bind();
    program->setUniformValue("n", 6);
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP); 
}

void EffectCRT::postFrame() 
{
    // unbind shader
    program->release();
}

