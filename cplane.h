#pragma once

#include <QtOpenGL>
#include <QtCore>

class CPlane {

typedef QVector2D vec2;
typedef QVector3D vec3;
typedef QVector4D vec4;

public:
  CPlane();
  ~CPlane();
  void draw(QOpenGLShaderProgram* prog);

private:
  void setupVAO(QOpenGLShaderProgram* prog);
  void initVAO();

protected:
  bool firstDraw;
  int size;
  vec3* vertices;
  vec3* normals;
  vec2* texture;
  QOpenGLVertexArrayObject* vao;
  QOpenGLBuffer* vbo;
};
