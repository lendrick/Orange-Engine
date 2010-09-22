#ifndef MAPSCENE_H
#define MAPSCENE_H

#include <QtCore>
#include <qgl.h>
#include "map.h"
#include "globals.h"

class mapBox;

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
  QAction * editGlobalScriptsAction;

  Entity * selectedEntity;
  QPoint mouseScreenPos;
  QPointF mouseScenePos;
  QFont * mapFont;

public slots:
  void newEntity();
  void deleteEntity();
  void editEntity();
  void editMapScripts();
  void editGlobalScripts();

signals:
  void showEntityDialog(Entity *);
  void showMapScriptDialog(Map *);
  void showGlobalScriptDialog();

private:
  void mousePressEvent(QGraphicsSceneMouseEvent * e);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent * e);
  void mouseMoveEvent(QGraphicsSceneMouseEvent * e);
  void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e);
  //void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
  //void dropEvent(QGraphicsSceneDragDropEvent *event);
  void keyPressEvent(QKeyEvent * event);
  void keyReleaseEvent(QKeyEvent * event);
  void keyEvent(int key, int eventType);
  //bool event(QEvent *event);
};

#endif // MAPSCENE_H
