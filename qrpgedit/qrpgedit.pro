#-------------------------------------------------
#
# Project created by QtCreator 2010-09-12T21:05:40
#
#-------------------------------------------------

QT       += core gui script opengl xml declarative

TARGET = qrpgedit
TEMPLATE = app
INCLUDEPATH = ../qrpglib
LIBS += -lSDL -lSDL_mixer
DESTDIR = ../qrpg-build-desktop

win32 {
    INCLUDEPATH +=../win32/include
    LIBS += -L../qrpg-build-desktop
}

SOURCES +=\
    rpgx_mapedit.cpp \
    gui.cpp \
    ../qrpglib/tileselect.cpp \
    ../qrpglib/talkbox.cpp \
    ../qrpglib/spritewidget.cpp \
    ../qrpglib/spritedialog.cpp \
    ../qrpglib/sprite.cpp \
    ../qrpglib/sound.cpp \
    ../qrpglib/scrollbar.cpp \
    ../qrpglib/scriptutils.cpp \
    ../qrpglib/scripttab.cpp \
    ../qrpglib/scriptdialog.cpp \
    ../qrpglib/rpgscript.cpp \
    ../qrpglib/rpgengine.cpp \
    ../qrpglib/resource.cpp \
    ../qrpglib/qrpgconsole.cpp \
    ../qrpglib/projectreader.cpp \
    ../qrpglib/project.cpp \
    ../qrpglib/polygon.cpp \
    ../qrpglib/newbitmapdialog.cpp \
    ../qrpglib/mapwindow.cpp \
    ../qrpglib/mapscriptdialog.cpp \
    ../qrpglib/globalscriptdialog.cpp \
    ../qrpglib/globals.cpp \
    ../qrpglib/mapscene.cpp \
    ../qrpglib/mapreader.cpp \
    ../qrpglib/mapbox.cpp \
    ../qrpglib/filebrowser.cpp \
    ../qrpglib/entityscripttab.cpp \
    ../qrpglib/entityscript.cpp \
    ../qrpglib/player.cpp \
    ../qrpglib/outlinestyle.cpp \
    ../qrpglib/npc.cpp \
    ../qrpglib/newprojectdialog.cpp \
    ../qrpglib/newmapdialog.cpp \
    ../qrpglib/newlayerdialog.cpp \
    ../qrpglib/map.cpp \
    ../qrpglib/layerpanel.cpp \
    ../qrpglib/jshighlighter.cpp \
    ../qrpglib/entitydialog.cpp \
    ../qrpglib/entity.cpp \
    ../qrpglib/coordinatewidget.cpp \
    ../qrpglib/input.cpp \
    ../qrpglib/imageframe.cpp \
    ../qrpglib/icons.cpp \
    ../qrpglib/collisiontester.cpp \
    ../qrpglib/boundswidget.cpp \
    ../qrpglib/bitmap_qt.cpp \
    ../qrpglib/propertyeditor.cpp \
    ../qrpglib/layerdialog.cpp

HEADERS  += \
    resource.h \
    gui.h \
    ../qrpglib/talkbox.h \
    ../qrpglib/spritewidget.h \
    ../qrpglib/spritedialog.h \
    ../qrpglib/sprite.h \
    ../qrpglib/sound.h \
    ../qrpglib/tileselect.h \
    ../qrpglib/scrollbar.h \
    ../qrpglib/scriptutils.h \
    ../qrpglib/scripttab.h \
    ../qrpglib/scriptdialog.h \
    ../qrpglib/rpgscript.h \
    ../qrpglib/rpgengine.h \
    ../qrpglib/qrpgconsole.h \
    ../qrpglib/projectreader.h \
    ../qrpglib/project.h \
    ../qrpglib/polygon.h \
    ../qrpglib/player.h \
    ../qrpglib/mapwindow.h \
    ../qrpglib/mapscriptdialog.h \
    ../qrpglib/globalscriptdialog.h \
    ../qrpglib/globals.h \
    ../qrpglib/filebrowser.h \
    ../qrpglib/mapscene.h \
    ../qrpglib/mapreader.h \
    ../qrpglib/mapbox.h \
    ../qrpglib/event.h \
    ../qrpglib/entityscripttab.h \
    ../qrpglib/entityscript.h \
    ../qrpglib/outlinestyle.h \
    ../qrpglib/npc.h \
    ../qrpglib/newprojectdialog.h \
    ../qrpglib/newmapdialog.h \
    ../qrpglib/newlayerdialog.h \
    ../qrpglib/newbitmapdialog.h \
    ../qrpglib/map.h \
    ../qrpglib/layerpanel.h \
    ../qrpglib/jshighlighter.h \
    ../qrpglib/entitydialog.h \
    ../qrpglib/entity.h \
    ../qrpglib/coordinatewidget.h \
    ../qrpglib/input.h \
    ../qrpglib/imageframe.h \
    ../qrpglib/icons.h \
    ../qrpglib/collisiontester.h \
    ../qrpglib/boundswidget.h \
    ../qrpglib/bitmap.h \
    ../qrpglib/propertyeditor.h \
    ../qrpglib/layerdialog.h

FORMS    +=
