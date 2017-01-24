#include <iostream>
#include "cplane.h"

using namespace std;

CPlane::CPlane(){
  size = 12;
  vertices = new vec3[size];
  normals = new vec3[size];
  texture = new vec2[size];
  int x = 0;

  vertices[0] = vec3(0,0, 0);
  vertices[1] = vec3(0,-1, 0); //bottom
  vertices[2] = vec3(1,-1, 1);

  vertices[3] = vec3(1,-1, 0); //bottom
  vertices[4] = vec3(2,0, 0);
  vertices[5] = vec3(2,-1, 0); //bottom

  vertices[6] = vec3(0, 1, 0); //top
  vertices[7] = vertices[0];
  vertices[8] = vec3(1, 1,  0); //top

  vertices[9] = vertices[2];
  vertices[10]= vec3(2, 1, 0); //top
  vertices[11]= vertices[4];

  texture[0] = vec2(0, 0.5);
  texture[1] = vec2(0, 0);
  texture[2] = vec2(.5, .5);
  texture[3] = vec2(.5, 0);
  texture[4] = vec2(1, .5);
  texture[5] = vec2(1, 0);
  texture[6] = vec2(0, 1);
  texture[7] = vec2(0, .5);
  texture[8] = vec2(.5, 1);
  texture[9] = vec2(.5, .5);
  texture[10]= vec2(1, 1);
  texture[11]= vec2(1, .5);

  //6 8 10
  //0 2 4
  //1 3 5
  normals[0] = vec3::crossProduct(vertices[1] - vertices[0], vertices[2]-vertices[0]) +
               vec3::crossProduct(vertices[2] - vertices[0], vertices[8]-vertices[0]) +
               vec3::crossProduct(vertices[8] - vertices[0], vertices[6]-vertices[0]);
  normals[1] =  vec3::crossProduct(vertices[2]-vertices[1],vertices[0]-vertices[1]) +
                vec3::crossProduct(vertices[3]-vertices[1],vertices[2]-vertices[1]);
  normals[2] =  vec3::crossProduct(vertices[0]-vertices[2],vertices[1]-vertices[2]) +
                vec3::crossProduct(vertices[1]-vertices[2],vertices[3]-vertices[2]) +
                vec3::crossProduct(vertices[3]-vertices[2],vertices[4]-vertices[2]) +
                vec3::crossProduct(vertices[4]-vertices[2],vertices[10]-vertices[2]) +
                vec3::crossProduct(vertices[10]-vertices[2],vertices[8]-vertices[2]) +
                vec3::crossProduct(vertices[8]-vertices[2],vertices[0]-vertices[2]);
  normals[3] =  vec3::crossProduct(vertices[2]-vertices[3],vertices[1]-vertices[3]) +
                vec3::crossProduct(vertices[5]-vertices[3],vertices[4]-vertices[3]) +
                vec3::crossProduct(vertices[4]-vertices[3],vertices[2]-vertices[3]);
  normals[4] = vec3::crossProduct(vertices[10]-vertices[4],vertices[2]-vertices[4]) +
               vec3::crossProduct(vertices[2]-vertices[4],vertices[3]-vertices[4]) +
               vec3::crossProduct(vertices[3]-vertices[4],vertices[5]-vertices[4]);
  normals[5] = vec3::crossProduct(vertices[10]-vertices[5],vertices[2]-vertices[5]) +
               vec3::crossProduct(vertices[2]-vertices[5],vertices[3]-vertices[5]) +
               vec3::crossProduct(vertices[3]-vertices[5],vertices[5]-vertices[5]);
  normals[6] = vec3::crossProduct(vertices[0]-vertices[6],vertices[2]-vertices[6]) +
               vec3::crossProduct(vertices[2]-vertices[6],vertices[8]-vertices[6]);
  normals[7] = normals[0];
  normals[8] = vec3::crossProduct(vertices[6]-vertices[8],vertices[0]-vertices[8]) +
               vec3::crossProduct(vertices[0]-vertices[8],vertices[2]-vertices[8]) +
               vec3::crossProduct(vertices[2]-vertices[8],vertices[10]-vertices[8]);
  normals[9] = normals[2];
  normals[10]= vec3::crossProduct(vertices[8]-vertices[10],vertices[4]-vertices[10]);
  normals[11]= normals[4];

  for (int i =0; i < size; i++){
    normals[i].normalize();
    cout << normals[i].x() << " " << normals[i].y() << " " << normals[i].z() << endl;
  }
  initVAO();
  vbo->bind();
  vbo->allocate(size*sizeof(vec3)
                + size*sizeof(vec3)
                + size*sizeof(vec2));
  vbo->write(0, vertices, size*sizeof(vec3));
  vbo->write(size*sizeof(vec3), normals, size*sizeof(vec3));
  vbo->write(size*sizeof(vec3)+size*sizeof(vec3), texture, size*sizeof(vec2));
  vbo->release();

  delete [] vertices; vertices=NULL;
  delete [] texture; texture=NULL;
}
CPlane::~CPlane(){
  if(vbo){
      vbo->release();
      delete vbo; vbo=NULL;
  }
  if(vao){
      vao->release();
      delete vao; vao=NULL;
  }
}
void CPlane::initVAO(){
  vao = new QOpenGLVertexArrayObject();
  vao->create();
  vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
  vbo->create();
  vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);
}
void CPlane::setupVAO(QOpenGLShaderProgram* prog){
  vao->bind();
  vbo->bind();

  prog->enableAttributeArray("vPosition");
  prog->setAttributeBuffer("vPosition", GL_FLOAT, 0, 3, 0);
  prog->enableAttributeArray("vNormal");
  prog->setAttributeBuffer("vNormal", GL_FLOAT, size*sizeof(vec3), 3, 0);
  prog->enableAttributeArray("vTexture");
  prog->setAttributeBuffer("vTexture", GL_FLOAT, size*sizeof(vec3)+size*sizeof(vec3), 2, 0);

  vao->release();
  vbo->release();
}
void CPlane::draw(QOpenGLShaderProgram* prog){
  if(!prog){
    return;
  }
  if(firstDraw){
    setupVAO(prog);
    firstDraw=false;
  }
  vao->bind();
  prog->setUniformValue("vColor", vec4(1,1,1,1));
  prog->setUniformValue("vSColor", vec4(1,1,1,1));
  glDrawArrays(GL_TRIANGLE_STRIP, 0, size/2);
  glDrawArrays(GL_TRIANGLE_STRIP, size/2, 6);
  vao->release();
}
