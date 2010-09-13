#ifndef SPRITEDIALOG_H
#define SPRITEDIALOG_H 1

#ifdef WIN32
#include <windows.h>
#endif
#include <QtGui>
#include <QGLWidget>
#include "spritewidget.h"
#include "tileselect.h"

class SpriteWidget;

class AddStateDialog : public QDialog {
  Q_OBJECT
public:
  static QString name();  
};

class AddSpriteDialog : public QDialog {
  Q_OBJECT
public:
  static QString name();  
};

class SpriteDialog : public QDialog {
  Q_OBJECT
public:
  SpriteDialog(QWidget * parent = 0);
private:
  QComboBox * currentSpriteBox;
  SpriteWidget * spriteWidget;
  QSlider * timeSlider;
  QLineEdit * spriteName;
  QComboBox * spriteTileset;
  QListWidget * stateList;
  QTableWidget * frameTable;
  TileSelect * tileSelect;

  QGroupBox * stateListBox;
  QGroupBox * frameTableBox;
  QGroupBox * spriteBox;
  QGroupBox * spriteInfoBox;

  QAction * addspriteAction;
  QAction * delspriteAction;

  QAction * playButton;
  QAction * stopButton;
  QAction * pauseButton;
  QAction * resetButton;

  QAction * frameAddAction;
  QAction * frameDelAction;
  QAction * stateAddAction;
  QAction * stateDelAction;

  Sprite * sprite;
  int durationColumn;
public slots:
  void updateSpritePulldown();
  void spriteChanged(QString);
  void tilesetChanged(QString);
  void stateChanged(int);
  void frameChanged(int);
  void tileChanged(int);
  void addSprite();
  void delSprite();
  void renameSprite(QString);
  void setCurrentSprite(QString);
  void setTileset(QString);
  void durationChanged(QTableWidgetItem *);
  void spriteNameChanged();
  void updateWidgets();
  void updateTilesets();
  void updateStates();
  void updateFrames();
  void updateSpriteSliderCurrent(int);
  void updateSpriteSliderDuration(int);
  void addState();
  void addFrame();
  void delState();
  void delFrame();
  void show();
  void disable(bool);
};

#endif