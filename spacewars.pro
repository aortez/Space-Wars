#-------------------------------------------------
#
# Project created by QtCreator 2011-12-16T22:40:19
#
#-------------------------------------------------

QT       += core gui

TARGET = spacewars
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    Circle.cpp \
    BoxOfShapes.cpp \
    Shape.cpp \
    InteractiveBoxOfShapes.cpp \
    Vec3f.cpp \
    Vec2f.cpp \
    rand.cpp \
    Vec3.cpp \
    Rect2f.cpp

HEADERS += \
    mainwindow.h \
    Circle.h \
    BoxOfShapes.h \
    Shape.h \
    SharedPtr.h \
    Vec3f.h \
    InteractiveBoxOfShapes.h \
    Vec2f.h \
    #Exploder.h \
    rand.h \
    Vec3.h \
    Rect2f.h

FORMS += mainwindow.ui

QT += opengl


















