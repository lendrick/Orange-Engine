#ifndef MAPBOX_H
#define MAPBOX_H 1

#ifdef WIN32
#include <windows.h>
#endif
#include <QtGui>
#include <qgl.h>
#include "map.h"
#include "globals.h"

class MapScene;
class Map;

class MapBox : public QGraphicsView {
  Q_OBJECT
  
  friend class MapScene;

public:
  MapBox(QWidget * parent=0);
  MapScene * mapScene;

public slots:
  void setX(int);
  void setY(int);
  void move(int, int);
  int getX();
  int getY();
  void setLayer(int);
  void addLayer(int, int, bool, QString);
  void deleteLayer(int);
  void setMap(int);
  Map * getMap();
  bool hasMap();
  //void LoadMap(char *);
  void saveMap(char *);
  LayerView::LayerViewMode getDrawMode();
  void setCamera(Entity *);
  Entity * getCamera();
  void setDrawMode(LayerView::LayerViewMode);
  void setCurrentTile(int);
  void addWidget(QWidget *);
  Entity * entityAt(int x, int y);
  QList < Entity * > entitiesAt(int x, int y);
  
  void setEditMode();
  void setEntityMode();
  void setSelectMode();
  void setBrushMode();
  void setMode(int mode);
  int getMode();
signals:
  void setXRange(int, int);
  void setYRange(int, int);
  void setXScroll(int);
  void setYScroll(int);
  void setLayerRange(int, int);
  void modeChanged(int);
  void mousePos(int, int, int, int);

private:
  void setTile(QMouseEvent * e);
  void setTile(QGraphicsSceneMouseEvent * e);
  void resizeEvent(QResizeEvent *event);
  
  Map * map;
  int xo, yo;
  int layer;
  int mouse_start_x, mouse_start_y;
  LayerView::LayerViewMode drawMode;
  int currentTile;
  int xrange, yrange;
  Entity * camera;
  Entity * dragEntity;
  int mapEditorMode;
};

class MapScene : public QGraphicsScene {
  Q_OBJECT

public:
  MapBox * mapBox;

  MapScene(MapBox * m);
  void drawBackground(QPainter *painter, const QRectF &rect);
  void init(int w, int h);
  void drawGrid(int layer, QPainter *painter, int tw, int th);
  void drawEntityNames(int layer, QPainter *painter);
  void drawNumbers(int layer, QPainter *painter, int tw, int th);
  QLabel * fpsLabel;
  QMenu * mapPopupMenu;
  QMenu * entityPopupMenu;

  QAction * newEntityAction;
  QAction * deleteEntityAction;
  QAction * editEntityAction;
  QAction * editMapScriptsAction;

  Entity * selectedEntity;
  QPoint mouseScreenPos;
  QPointF mouseScenePos;
  QFont * mapFont;
  
public slots:
  void newEntity();
  void deleteEntity();
  void editEntity();
  void editMapScripts();
  
signals:
  void showEntityDialog(Entity *);
  void showMapScriptDialog(Map *);
  
private:
  void mousePressEvent(QGraphicsSceneMouseEvent * e);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent * e);
  void mouseMoveEvent(QGraphicsSceneMouseEvent * e);
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e);
  void keyPressEvent(QKeyEvent * event);
  void keyReleaseEvent(QKeyEvent * event);
  void keyEvent(int key, int eventType);
};

#endif
