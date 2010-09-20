#ifndef TILESELECT_H
#define TILESELECT_H 1
#ifdef WIN32
#include <windows.h>
#endif
#include <qwidget.h>
#include <qgl.h>
#include <qevent.h>
#include <qscrollbar.h>
#include "bitmap.h"

class Bitmap;

class TileBox : public QGLWidget {
  Q_OBJECT
public:
  TileBox(QWidget * parent=0);
  void setTileset(Bitmap * t);
  int getSelected();
public slots:
  void setScroll(int);
  void setSelected(int);
signals:
  void setRange(int, int);
  void tileChanged(int);
private:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  void mousePressEvent(QMouseEvent * e);

  Bitmap * tileset;
  int selected;
  int scroll;
};

class TileSelect : public QWidget {
  Q_OBJECT
public:
  TileSelect(QWidget *parent=0);
  void setTileset(Bitmap * t);
  int getTile();
  TileBox * tilebox;
public slots:
  void setTiles(int);

private:
  QScrollBar * scroll;
};

#endif
