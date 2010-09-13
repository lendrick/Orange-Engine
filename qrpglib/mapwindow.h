#ifndef MAPWINDOW_H
#define MAPWINDOW_H 1

#ifdef WIN32
#include <windows.h>
#endif
#include <QtGui>
#include <qgl.h>
#include "map.h"
#include "globals.h"
#include "mapbox.h"

class MapScene;
class Map;
class MapBox;

class MapWindow : public QWidget {
  Q_OBJECT
public:
  MapWindow(QWidget *parent=0);
  MapBox * mapbox;
private:
  QStatusBar * status;
signals:
  void setDrawMode(LayerView::LayerViewMode);
public slots:
  void updateStatus(QString s);
};

#endif
