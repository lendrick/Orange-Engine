#ifdef WIN32
#include <windows.h>
#endif

#include "mapbox.h"
#include "bitmap.h"
#include "tileselect.h"
#include "map.h"

#include <qgl.h>
#include <QtGui>
#include <qtimer.h>
#include <iostream>
#include <vector>
#include <QTime>

#include "globals.h"
#include "scrollbar.h"
#include "outlinestyle.h"
#include "input.h"
#include "entity.h"
#include "player.h"
#include "qrpgconsole.h"
#include "talkbox.h"
#include "rpgengine.h"
#include "rpgscript.h"
#include "mapscene.h"

using std::cout;


MapBox::MapBox(QWidget * parent) :
  QDeclarativeView(parent) {
  map = 0;
  xo = 0;
  yo = 0;
  mouse_start_x = 0;
  mouse_start_y = 0;
  currentTile = 0;
  mapScene = new MapScene(this);
  drawMode = LayerView::All;
  //camera = 0;
  mapEditorMode = MapEditorMode::Edit;

  this->setFrameStyle(QFrame::NoFrame);
  this->setStyleSheet("border-style: none; padding: 0; margin: 0");
  this->setContentsMargins(0, 0, 0, 0);

  QGLWidget * viewport = new QGLWidget(this, mainGLWidget);
  viewport->setStyleSheet("border-style: none; padding: 0; margin: 0;");
  viewport->setContentsMargins(0, 0, 0, 0);
  this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers), 0, mainGLWidget));
  this->setViewport(viewport);
  this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  this->setScene(mapScene);
  this->setMouseTracking(true);
  setDragMode(QGraphicsView::RubberBandDrag);
}

void MapBox::setCurrentTile(int t) {
  currentTile = t;
}

void MapBox::setCamera(EntityPointer c) {
  camera = c;
  layer = c->getLayer();
}

EntityPointer MapBox::getCamera() {
  return camera;
}

void MapBox::addWidget(QWidget * w) {
  mapScene->addWidget(w);
}



void MapBox::resizeEvent(QResizeEvent *event) {
  int w, h, lw, lh, tw, th;
  
  w = event->size().width();
  h = event->size().height();

  screen_x = w;
  screen_y = h;

  if(map) {
    map->getSize(layer, lw, lh);
    map->getTileSize(tw, th);
    map->setViewport(0, 0, w, h);
    
    emit setXRange(0, tw * lw - w);
    emit setYRange(0, th * lh - h);

    xrange = tw * lw - w;
    yrange = th * lh - h;
  }
  
  if (scene())
    scene()->setSceneRect(QRect(QPoint(0, 0), event->size()));
  QGraphicsView::resizeEvent(event);
}


void MapBox::setX(int x) {
  //makeCurrent();
  xo = x;

  if(xo < 0) xo = 0;
  if(xo >= xrange) xo = xrange;
  if(xo < 0) xo /= 2;
  //updateGL();
  update();
}

void MapBox::setY(int y) {
  //makeCurrent();
  yo = y;

  if(yo < 0) yo = 0;
  if(yo >= yrange) yo = yrange;
  if(yo < 0) yo /= 2;
  //updateGL();
  update();
}

int MapBox::getX() {
  return xo;
}

int MapBox::getY() {
  return yo;
}

void MapBox::move(int dx, int dy) {
  setX(xo + dx);
  setY(yo + dy);
}

void MapBox::setTile(QMouseEvent * e) {
  if(map) {
    int w, h, x, y;
    
    map->getTileSize(w, h);
    x = (xo + e->x()) / w;
    y = (yo + e->y()) / h;
    
    map->setTile(layer, x, y, currentTile);
    //makeCurrent();
    //updateGL();
    update();
  }
}  

void MapBox::setTile(QGraphicsSceneMouseEvent * e) {
  if(map) {
    int w, h, x, y;
    
    map->getTileSize(w, h);
    x = (xo + e->scenePos().x()) / w;
    y = (yo + e->scenePos().y()) / h;
    
    map->setTile(layer, x, y, currentTile);
    //makeCurrent();
    //updateGL();
    update();
  }
}  

void MapBox::setLayer(int l) {
  if(layer >= 0 && layer < map->getLayerCount()) {
    int lw, lh, tw, th;
    layer = l;

    map->getSize(layer, lw, lh);
    map->getTileSize(tw, th);
    
    emit setXRange(0, tw * lw - width());
    emit setYRange(0, th * lh - height());

    xrange = tw * lw - width();
    yrange = th * lh - height();
    //makeCurrent();
    //updateGL();
    update();
  }
}
	 

void MapBox::addLayer(int w, int h, bool wrap, QString name) {
  if(map) {
    int filltile = currentTile;
    map->addLayer(w, h, wrap, filltile, name);
    emit setLayerRange(0, map->getLayerCount() - 1);
    if(map->getLayerCount() == 1) {
      int lw, lh, tw, th;

      map->getSize(0, lw, lh);
      map->getTileSize(tw, th);
    
      emit setXRange(0, tw * lw - width());
      emit setYRange(0, th * lh - height());

      xrange = tw * lw - width();
      yrange = th * lh - height();
    }
  }  
}

void MapBox::deleteLayer(int layer) {
  map->deleteLayer(layer);
  if(map->getLayerCount() < layer) layer = map->getLayerCount();
  setLayer(layer);
}

bool MapBox::hasMap() {
  if(map) {
    return true;
  } else {
    return false;
  }
}

Map * MapBox::getMap() {
  return map;
}

void MapBox::setMap(int map_num) {
  int lw, lh, tw, th, w, h;

  if(map)
    map->runUnLoadScripts();

  map = 0;
  RPGEngine::setCurrentMap(0);
  if(map_num >= 0) {
    map = maps[map_num];
  }
  layer = 0;
  w = width();
  h = height();

  mapScene->init(w, h);
  if (scene())
    scene()->setSceneRect(QRect(QPoint(0, 0), QPoint(w, h)));

  if(map) {
    map->getSize(layer, lw, lh);
    map->getTileSize(tw, th);
    map->setViewport(0, 0, w, h);
    map->setStarting(true);
    
    emit setXRange(0, tw * lw - w);
    emit setYRange(0, th * lh - h);
    
    xrange = tw * lw - w;
    yrange = th * lh - h;

    if(map->getLayerCount() == 0) {
      emit setLayerRange(0, 0);
    } else {
      emit setLayerRange(0, map->getLayerCount() - 1);
    }

    RPGEngine::setCurrentMap(map);

    QScriptValue objectValue = scriptEngine->newQObject(map);
    scriptEngine->globalObject().setProperty("map", objectValue);
  } else {
    scriptEngine->globalObject().setProperty("map", QScriptValue(QScriptValue::NullValue));
  }
  
}


void MapBox::saveMap(char * filename) {
  if(map) map->save(filename);
}

//void MapBox::LoadMap(char * filename) {
  //if(map) map->Load(filename);
//}

void MapBox::setDrawMode(LayerView::LayerViewMode mode) {
  drawMode = mode;
}

void MapBox::setEditMode() {
  setMode(MapEditorMode::Edit);
}

void MapBox::setEntityMode() {
  setMode(MapEditorMode::Entity);
}

void MapBox::setSelectMode() {
  setMode(MapEditorMode::Select);
}

void MapBox::setBrushMode() {
  setMode(MapEditorMode::Brush);
}

void MapBox::setMode(int mode) {
  mapEditorMode = mode;
  emit modeChanged(mode);
}

int MapBox::getMode() {
  return mapEditorMode;
}

EntityPointer MapBox::entityAt(int x, int y) {
  if(map && map->getLayerCount() > 0) {
    double x1, y1, x2, y2;
    if(play) {
      // Count down from the top, so we know we'll get the ones on top first.
      for(int i = map->getEntityCount(layer) - 1; i >= 0; i--) {
        map->getEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) return map->getEntity(layer, i);
      }
    } else {
      for(int i = map->getStartEntityCount(layer) - 1; i >= 0; i--) {
        map->getStartEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        /*
        message(QString::number(x) + ", " + QString::number(y) + "\n"
                + map->getStartEntity(layer, i)->getName() + ": "
                + QString::number(x1) + " " + QString::number(y1) + " / "
                + QString::number(x2) + " " + QString::number(y2) + " ");
                */
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) return map->getStartEntity(layer, i);
      }
    }
  }
  return EntityPointer();
}

QList < EntityPointer > MapBox::entitiesAt(int x, int y) {
  QList < EntityPointer > entities;

  if(map && map->getLayerCount() > 0) {
    double x1, y1, x2, y2;
    if(play) {
      // Count down from the top, so we know we'll get the ones on top first.
      for(int i = map->getEntityCount(layer) - 1; i >= 0; i--) {
        map->getEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) entities.append(map->getEntity(layer, i));
      }
    } else {
      for(int i = map->getStartEntityCount(layer) - 1; i >= 0; i--) {
        map->getStartEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) entities.append(map->getStartEntity(layer, i));
      }
    }
  }

  return entities;
}

Map::Layer * MapBox::getCurrentLayer() {
  return map->layers[layer];
}

/*
bool MapBox::viewportEvent(QEvent *event) {
  if(event->type() != QEvent::Paint && event->type() != QEvent::UpdateRequest)
    qDebug() << "MapBox::viewportEvent: " << event;
  return QGraphicsView::viewportEvent(event);
  //event->accept();
}

void MapBox::mouseReleaseEvent(QMouseEvent * event) {
  //releaseMouse();
  qDebug() << "MapBox::mouseReleaseEvent " << event;
  //RPGEngine::dumpEvent(event);
  //event->accept();
  QGraphicsView::mouseReleaseEvent(event);
}

void MapBox::mousePressEvent(QMouseEvent * event) {
  //grabMouse();
  qDebug() << "\n\nMapBox::mousePressEvent " <<  event << " " << dragMode();
  //RPGEngine::dumpEvent(event);
  //event->accept();
  QGraphicsView::mousePressEvent(event);
}


void MapBox::mouseMoveEvent(QMouseEvent *event) {
  qDebug() << "MapBox::mouseMoveEvent" << event;
  QGraphicsView::mouseMoveEvent(event);
  //event->accept();
}

bool MapBox::eventFilter(QObject * watched, QEvent * event) {
  qDebug() << "MapBox::eventFilter: " << RPGEngine::eventName(event);
  return QGraphicsView::eventFilter(watched, event);
}


bool MapBox::event(QEvent *event)
{
  if(event->type() != 43) {
    //qDebug() << "MapBox: " << RPGEngine::eventName(event);
  }
  return QGraphicsView::event(event);
}
*/

LayerView::LayerViewMode MapBox::getDrawMode() {
  return drawMode;
}
  
