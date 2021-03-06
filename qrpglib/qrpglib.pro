#-------------------------------------------------
#
# Project created by QtCreator 2010-09-12T20:25:46
#
#-------------------------------------------------

QT       += opengl script xml

TARGET = qrpglib
TEMPLATE = lib
DESTDIR = ../qrpg-build-desktop
LIBS += -lSDL_mixer

DEFINES += QRPGLIB_LIBRARY

SOURCES += \
    tileselect.cpp \
    talkbox.cpp \
    spritewidget.cpp \
    spritedialog.cpp \
    sprite.cpp \
    scrollbar.cpp \
    scriptutils.cpp \
    qrpgconsole.cpp \
    project.cpp \
    polygon.cpp \
    player.cpp \
    outlinestyle.cpp \
    npc.cpp \
    newprojectdialog.cpp \
    newmapdialog.cpp \
    newlayerdialog.cpp \
    newbitmapdialog.cpp \
    mapwindow.cpp \
    mapbox.cpp \
    map.cpp \
    layerpanel.cpp \
    input.cpp \
    imageframe.cpp \
    icons.cpp \
    globals.cpp \
    filebrowser.cpp \
    entitydialog.cpp \
    entity.cpp \
    collisiontester.cpp \
    bitmap_qt.cpp \
    resource.cpp \
    jshighlighter.cpp \
    scriptdialog.cpp \
    scripttab.cpp \
    mapreader.cpp \
    rpgengine.cpp \
    sound.cpp \
    mapscriptdialog.cpp \
    entityscripttab.cpp \
    globalscriptdialog.cpp \
    rpgscript.cpp \
    projectreader.cpp \
    mapscene.cpp \
    coordinatewidget.cpp \
    boundswidget.cpp \
    entityscript.cpp

HEADERS +=\
    tileselect.h \
    talkbox.h \
    spritewidget.h \
    spritedialog.h \
    sprite.h \
    scrollbar.h \
    scriptutils.h \
    resource.h \
    qrpgconsole.h \
    project.h \
    polygon.h \
    player.h \
    outlinestyle.h \
    npc.h \
    newprojectdialog.h \
    newmapdialog.h \
    newlayerdialog.h \
    newbitmapdialog.h \
    mapwindow.h \
    mapbox.h \
    map.h \
    layerpanel.h \
    input.h \
    imageframe.h \
    icons.h \
    globals.h \
    filebrowser.h \
    event.h \
    entitydialog.h \
    entity.h \
    collisiontester.h \
    bitmap.h \
    jshighlighter.h \
    scriptdialog.h \
    scripttab.h \
    mapreader.h \
    qrpgengine.h \
    rpgengine.h \
    sound.h \
    mapscriptdialog.h \
    entityscripttab.h \
    globalscriptdialog.h \
    rpgscript.h \
    projectreader.h \
    mapscene.h \
    coordinatewidget.h \
    boundswidget.h \
    entityscript.h
