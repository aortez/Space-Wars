QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    Rectangle.cpp

HEADERS += \
    mainwindow.h \
    Circle.h \
    BoxOfShapes.h \
    Shape.h \
    SharedPtr.h \
    Vec3f.h \
    InteractiveBoxOfShapes.h \
    Vec2f.h \
    rand.h \
    Vec3.h \
    Rectangle.h

FORMS += mainwindow.ui

QT += opengl


















