#-------------------------------------------------
#
# Project created by QtCreator 2010-09-12T20:43:12
#
#-------------------------------------------------

QT       += core gui script opengl

TARGET = qrpgengine
TEMPLATE = app
INCLUDEPATH = ../qrpglib
LIBS += -L../qrpglib-build-desktop -lqrpglib

SOURCES +=\
    qrpgengine.cpp \
    enginewindow.cpp

HEADERS  += \
    enginewindow.h

FORMS    +=
