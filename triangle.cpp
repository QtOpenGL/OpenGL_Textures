#include "triangle.h"
#include <iostream>

using namespace std;

Triangle::Triangle(){
	m_firstDraw = true;
    vec4* vertices = new QVector4D[3];
    vertices[0] = QVector4D(1.0, 1.0, 0., 1.);
    vertices[1] = QVector4D(0.0, 1.0, 0., 1.);
    vertices[2] = QVector4D(1.0, -1.0, 0., 1.);


    vec2* texture = new vec2[3];
    texture[0] = vec2(1.0, 1.0);
    texture[1] = vec2(0.50, 1.0);
    texture[2] = vec2(1.0, 0.0);

	// //initialize vao
	vao = new QOpenGLVertexArrayObject();
	vao->create();
	// //initialize vbo
	vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vbo->create();
	vbo->setUsagePattern(QOpenGLBuffer::StaticDraw);

	//pass data to vbo
	vbo->bind();
	// // vbo->allocate(dataSize);
	vbo->allocate(3*sizeof(vec4)+3*sizeof(vec2));
	vbo->write(0, vertices, 3*sizeof(vec4));
	// vbo->write(3*sizeof(vec4), normals ,3*sizeof(vec4));
	vbo->write(3*sizeof(vec4), texture, 3*sizeof(vec2));
	vbo->release();

	delete[] vertices;
	vertices = NULL;
	// delete[] normals;
	// normals = NULL;
	delete[] texture;
	texture = NULL;
}
Triangle::~Triangle() {
  if (vbo) {
    vbo->release();
    delete vbo;
    vbo = NULL;
  }
  if (vao) {
    vao->release();
    delete vao;
    vao = NULL;
  }
}
QVector4D* Triangle::createVertices(){
    vec4* verts = new QVector4D[3];
    verts[0] = QVector4D(-1.0, -1.0, 0., 1.);
    verts[1] = QVector4D(0.0, 1.0, 0., 1.);
    verts[2] = QVector4D(1.0, -1.0, 0., 1.);
    return verts;
}

void Triangle::setupVAO(QOpenGLShaderProgram* prog){
	vao->bind();
	vbo->bind();

	prog->enableAttributeArray("vPosition");
	prog->setAttributeBuffer("vPosition", GL_FLOAT, 0, 4, 0);
	prog->enableAttributeArray("vTexture");
	prog->setAttributeBuffer("vTexture", GL_FLOAT, 3*sizeof(vec4), 2, 0);

	vao->release();
	vbo->release();
}
void Triangle::draw(QOpenGLShaderProgram* prog){
	if(!prog){
		return;
	}
	if(m_firstDraw){
		setupVAO(prog);
		m_firstDraw = false;
	}
	vao->bind();
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
	vao->release();
}
