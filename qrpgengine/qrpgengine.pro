#-------------------------------------------------
#
# Project created by QtCreator 2010-09-12T20:43:12
#
#-------------------------------------------------

QT       += core gui script opengl xml declarative qtquick1 quick

TARGET = orange
TEMPLATE = app
LIBS += -lSDL_mixer -lSDL
DESTDIR = ../qrpg-build-desktop
INCLUDEPATH = ../qrpglib

win32 {
    INCLUDEPATH +=../win32/include
    LIBS += -L../qrpg-build-desktop
}

SOURCES +=\
    qrpgengine.cpp \
    enginewindow.cpp \
    ../qrpglib/tileselect.cpp \
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
    ../qrpglib/icons.cpp \
    ../qrpglib/collisiontester.cpp \
    ../qrpglib/boundswidget.cpp \
    ../qrpglib/bitmap_qt.cpp \
    ../qrpglib/layerdialog.cpp \
    ../qrpglib/qmlutils.cpp

HEADERS  += \
    enginewindow.h \
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
    ../qrpglib/resource.h \
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
    ../qrpglib/icons.h \
    ../qrpglib/collisiontester.h \
    ../qrpglib/boundswidget.h \
    ../qrpglib/bitmap.h \
    ../qrpglib/layerdialog.h \
    ../qrpglib/qmlutils.h \
    ../qrpglib/qdeclarativedebughelper_p.h

FORMS    +=

OTHER_FILES += \
    ../qrpg-build-desktop/interface/Box.qml \
    ../qrpg-build-desktop/interface/BigText.qml \
    ../qrpg-build-desktop/interface/TalkBoxText.qml \
    ../qrpg-build-desktop/interface/SimpleMenu.qml \
    ../qrpg-build-desktop/interface/SimpleMenu.js \
    ../qrpg-build-desktop/interface/SimpleMenuItem.qml \
    ../qrpg-build-desktop/interface/MediumText.qml \
    ../qrpg-build-desktop/interface/HideShowContainer.qml \
    ../qrpg-build-desktop/Tech Demo 2/scripts/characters.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/startup.js \
    ../qrpg-build-desktop/interface/PartyScreen.qml \
    ../qrpg-build-desktop/interface/CharacterScreen.qml \
    ../qrpg-build-desktop/interface/PartyScreen.js \
    ../qrpg-build-desktop/interface/CharacterScreen.js \
    ../qrpg-build-desktop/interface/SmallText.qml \
    ../qrpg-build-desktop/interface/StatItem.qml \
    ../qrpg-build-desktop/interface/BindItem.qml \
    ../qrpg-build-desktop/Tech Demo 2/qml/Character.qml \
    ../qrpg-build-desktop/Tech Demo 2/qml/Character.js \
    ../qrpg-build-desktop/interface/ImageMenuItem.qml \
    ../qrpg-build-desktop/Tech Demo 2/qml/CharacterItemSlot.qml \
    ../qrpg-build-desktop/interface/SlotItem.qml \
    ../qrpg-build-desktop/Tech Demo 2/scripts/Ability.qml \
    ../qrpg-build-desktop/Tech Demo 2/scripts/items.js \
    ../qrpg-build-desktop/interface/ItemScreen.qml \
    ../qrpg-build-desktop/interface/ItemScreen.js \
    ../qrpg-build-desktop/interface/InventoryItem.qml \
    ../qrpg-build-desktop/interface/PortraitMenu.qml \
    ../qrpg-build-desktop/interface/PortraitMenu.js \
    ../qrpg-build-desktop/interface/MagicScreen.qml \
    ../qrpg-build-desktop/interface/MagicScreen.js \
    ../qrpg-build-desktop/Tech Demo 2/qml/Ability.js \
    ../qrpg-build-desktop/interface/Ui.qml \
    ../qrpg-build-desktop/interface/Ui.js \
    ../qrpg-build-desktop/interface/CharacterItemSlot.qml \
    ../qrpg-build-desktop/interface/Character.js \
    ../qrpg-build-desktop/interface/Character.qml \
    ../qrpg-build-desktop/interface/CharacterItemSlot.js \
    ../qrpg-build-desktop/interface/CharacterMagicScreen.qml \
    ../qrpg-build-desktop/interface/CharacterMagicScreen.js \
    ../qrpg-build-desktop/interface/AbilityItem.qml \
    ../qrpg-build-desktop/interface/TreeMenuItem.qml \
    ../qrpg-build-desktop/interface/TreeMenu.qml \
    ../qrpg-build-desktop/interface/TreeMenu.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/sfx.js \
    ../qrpg-build-desktop/interface/InventoryItem.js \
    ../qrpg-build-desktop/interface/ModalItemScreen.qml \
    ../qrpg-build-desktop/interface/BattleScreen.qml \
    ../qrpg-build-desktop/interface/CharacterBox.qml \
    ../qrpg-build-desktop/interface/BattleScreen.js \
    ../qrpg-build-desktop/Tech Demo 2/shaders/blur_v.glsl \
    ../qrpg-build-desktop/Tech Demo 2/shaders/blur_h.glsl \
    ../qrpg-build-desktop/interface/BattleEnemy.qml \
    ../qrpg-build-desktop/interface/CharacterBox.js \
    ../qrpg-build-desktop/interface/DamageNumber.qml \
    ../qrpg-build-desktop/interface/TreeMenuNode.qml \
    ../qrpg-build-desktop/interface/BaseItem.qml \
    ../qrpg-build-desktop/interface/BaseItem.js \
    ../qrpg-build-desktop/interface/animations/Fire1.qml \
    ../qrpg-build-desktop/interface/animations/Bludgeon1.qml \
    ../qrpg-build-desktop/interface/MessageBox.qml \
    ../qrpg-build-desktop/Tech Demo 2/scripts/startup.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/sfx.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/json2.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/items.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/init.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/functions.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/enemy_ai.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/characters.js \
    ../qrpg-build-desktop/Tech Demo 2/scripts/abilities.js \
    ../qrpg-build-desktop/interface/TalkBoxText.js


