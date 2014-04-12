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
    Vec2f.cpp \
    Rectangle.cpp \
    prng.cpp

HEADERS += \
    mainwindow.h \
    Circle.h \
    BoxOfShapes.h \
    Shape.h \
    SharedPtr.h \
    InteractiveBoxOfShapes.h \
    Vec2f.h \
    Rectangle.h \
    prng.h

FORMS += mainwindow.ui

QT += opengl


















