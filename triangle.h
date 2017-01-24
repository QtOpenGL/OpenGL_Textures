#pragma once 

#include <QtOpenGL>
#include <QtCore>

class Triangle{

	typedef QVector2D vec2; 
	typedef QVector3D vec3;
	typedef QVector4D vec4; 
public:

	Triangle(); 
	~Triangle(); 
	
	/* Takes in program that holds the shaders */ 
	void draw(QOpenGLShaderProgram* prog); 
	QVector4D* createVertices();

	// inline void setColor(const vec3& color){ this->color = color; this->color.setW(1.); }
	// inline vec4 getColor()const { return color; }

private:
	void setupVAO(QOpenGLShaderProgram* prog);

protected:
	vec4* color; 
	vec4* vertices; 
	QOpenGLVertexArrayObject* vao; 
	QOpenGLBuffer* vbo; 
	int dataSize; 
	bool m_firstDraw; 
}; 