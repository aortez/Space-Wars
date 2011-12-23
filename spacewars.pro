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
    Point2f.cpp \
    InteractiveBoxOfShapes.cpp

HEADERS += \
    mainwindow.h \
    Circle.h \
    BoxOfShapes.h \
    Shape.h \
    SharedPtr.h \
    Point2f.h \
    Vec3f.h \
    InteractiveBoxOfShapes.h

FORMS += mainwindow.ui

QT += opengl
