#include "mypanelopengl.h"
#include <cmath>
#include <iostream>

using namespace std;

MyPanelOpenGL::MyPanelOpenGL(QWidget *parent) :
  QOpenGLWidget(parent) {

    shaderProgram=NULL;
    vertexShader=NULL;
    fragmentShader=NULL;
    polymode = 1;
    vboVertices = NULL;
    vao = NULL;

    numVertices = 3;
}

MyPanelOpenGL::~MyPanelOpenGL(){
  destroyShaders();
}

void MyPanelOpenGL::initializeGL()
{
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glFrontFace(GL_CW);

  glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
  createShaders();

  triangle = new Triangle();        // Comment 1
  square = new Square(1);           // Comment 2
  sphere = new Sphere(.5,40,40);    // Comment 3
  plane = new CPlane();             // Comment 4

  model.setToIdentity();
  /* CAMERA:  eye ---- center ---- up direction */
  camera.lookAt(vec3(0,0, 3),vec3(0,0,0),vec3(0, 1,0));
  texture = new QOpenGLTexture(QImage(":/build/earth.png").mirrored());

}
void MyPanelOpenGL::resizeGL(int w, int h)
{
  glViewport(0,0,w, h);
}

void MyPanelOpenGL::paintGL(){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // glEnable(GL_TEXTURE_2D);

  updatePolyMode(polymode);

  texture->bind();
  shaderProgram->bind();


  view.setToIdentity();
  //verticalAngle, aspectRatio, nearPlane, farPlane
  view.perspective(65, 1, 1, 10);

  // view = view * camera;
  // view.setToIdentity();
  // camera.setToIdentity();11

  model.setToIdentity();
  model.rotate(m_angles.x(), vec3(1,0,0));
  model.rotate(m_angles.y(), vec3(0,1,0));
  model.rotate(m_angles.z(), vec3(0,0,1));

  // view.ortho(-2,2,-2,2,-2,2);
  shaderProgram->setUniformValue("camera", camera);
  shaderProgram->setUniformValue("model", model);
  shaderProgram->setUniformValue("view",view);
  shaderProgram->setUniformValue("Tex0",0);
  shaderProgram->setUniformValue("lightPos", vec4(1, 0, 4, 1.));

  mat4 mview = camera * model;
  shaderProgram->setUniformValue("modelView", mview);
  shaderProgram->setUniformValue("normalMatrix", mview.normalMatrix());

  triangle->draw(shaderProgram);    // Comment 1
  sphere->draw(shaderProgram);      // Comment 2
  square->draw(shaderProgram);      // Comment 3
  plane->draw(shaderProgram);       // Comment 4

  glFlush();
}
void MyPanelOpenGL::createShaders(){
  destroyShaders(); //get rid of any old shaders

  vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
  if (!vertexShader->compileSourceFile(":/shaders/vshader.glsl")){
    qWarning() << vertexShader->log();
  }

  fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
  if(!fragmentShader->compileSourceFile(":/shaders/fshader.glsl")){
    qWarning() << fragmentShader->log();
  }

  shaderProgram = new QOpenGLShaderProgram();
  shaderProgram->addShader(vertexShader);
  shaderProgram->addShader(fragmentShader);
  

  if(!shaderProgram->link()){
    qWarning() << shaderProgram->log() << endl;
  }
}
void MyPanelOpenGL::keyPressEvent(QKeyEvent *event)
{
  /*Enable strong Focus on GL Widget to process key events*/
  int step = 2;
  switch(event->key()){
  case Qt::Key_P:
      polymode = (polymode + 1) % 3;
      updatePolyMode(polymode);
      break;
  case Qt::Key_X:
      if (event->text()=="x"){updateAngles(0,step);}
      else{updateAngles(0,-step);}
      break;
  case Qt::Key_Y:
      if (event->text()=="y"){ updateAngles(1,step);}
      else{ updateAngles(1,-step);}
      break;
  case Qt::Key_Z:
      if (event->text()=="z"){updateAngles(2,step);}
      else{updateAngles(2,-step);}
      break;
  case Qt::Key_Left:
    cout << "moving" << endl;
      model.translate(-1,0);
      break;
  case Qt::Key_Right:
      model.translate(1,0);
      break;
  }
  update();
}
void MyPanelOpenGL::updateAngles(int idx, qreal amt){
    if(idx == 0){
        m_angles.setX(m_angles.x()+amt);
    }else if(idx == 1){
        m_angles.setY(m_angles.y()+amt);
    }else if(idx == 2){
        m_angles.setZ(m_angles.z()+amt);
    }
}
void MyPanelOpenGL::updatePolyMode(int val){
    GLenum mode=GL_NONE;
    if(val==0){mode=GL_POINT;}
    else if(val==1){mode=GL_LINE;}
    else if(val==2){mode=GL_FILL;}

    if(mode != GL_NONE){
        glPolygonMode(GL_FRONT_AND_BACK, mode);
    }
}
void MyPanelOpenGL::destroyShaders(){
  delete vertexShader; vertexShader=NULL;
  delete fragmentShader; fragmentShader=NULL;

  if(shaderProgram){
    shaderProgram->release();
    delete shaderProgram; shaderProgram=NULL;
  }
}
