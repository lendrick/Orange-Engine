#-------------------------------------------------
#
# Project created by QtCreator 2010-09-12T21:05:40
#
#-------------------------------------------------

QT       += core gui script opengl

TARGET = qrpgedit
TEMPLATE = app
INCLUDEPATH = ../qrpglib
LIBS += -L../qrpglib-build-desktop -lqrpglib

SOURCES +=\
    rpgx_mapedit.cpp \
    gui.cpp

HEADERS  += \
    resource.h \
    gui.h

FORMS    +=
