#ifndef MYPANELOPENGL_H
#define MYPANELOPENGL_H

#include <QtWidgets>
#include <QtOpenGL>
#include "triangle.h"
#include "sphere.h"
#include "square.h"
#include "cplane.h"

typedef QVector3D vec3;
typedef QMatrix4x4 mat4;

class MyPanelOpenGL : public QOpenGLWidget
{
    Q_OBJECT

    protected:
        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();
        void keyPressEvent(QKeyEvent* event);

    public:
        explicit MyPanelOpenGL(QWidget *parent = 0);
        virtual ~MyPanelOpenGL();

    private:
        void createShaders();
        void destroyShaders();

        void updateAngles(int idx, qreal amt);
        void updatePolyMode(int val);


        QMatrix4x4 model;
        QMatrix4x4 camera;
        QMatrix4x4 view;
        QMatrix4x4 translate;

        Triangle* triangle;
        Square* square;
        Sphere* sphere;
        CPlane* plane;

        unsigned int numVertices;
        QVector4D *vertices;
        vec3 m_angles;

        int polymode;

        /* VAO required in core profile */
        QOpenGLVertexArrayObject *vao;
        QOpenGLBuffer *vboVertices;


        QOpenGLTexture* texture;
        QOpenGLShader*  vertexShader;
        QOpenGLShader*  fragmentShader;
        QOpenGLShader*  geomShader; 
        QOpenGLShaderProgram* shaderProgram;

signals:

public slots:

};

#endif // MYPANELOPENGL_H
