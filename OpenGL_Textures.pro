#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T14:34:24
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL_Textures
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    cplane.cpp \
    mypanelopengl.cpp \
    sphere.cpp \
    square.cpp \
    triangle.cpp

HEADERS  += mainwindow.h \
    cplane.h \
    mypanelopengl.h \
    sphere.h \
    square.h \
    triangle.h

FORMS    += mainwindow.ui

DISTFILES +=

RESOURCES += \
    resources.qrc

LIBS += -lopengl32
