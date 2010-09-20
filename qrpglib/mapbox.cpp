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

using std::cout;

int frames = 0;
int framesThisSecond = 0;

MapBox::MapBox(QWidget * parent) :
  QGraphicsView(parent) {
  map = 0;
  xo = 0;
  yo = 0;
  mouse_start_x = 0;
  mouse_start_y = 0;
  currentTile = 0;
  mapScene = new MapScene(this);
  drawMode = LayerView::All;
  camera = 0;
  mapEditorMode = MapEditorMode::Edit;
  
  //this->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers), 0, mainGLWidget));
  this->setStyleSheet("border-style: none; padding: 0;");
  this->setViewport(new QGLWidget(this, mainGLWidget));
  this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
  this->setScene(mapScene);
}

void MapBox::setCurrentTile(int t) {
  currentTile = t;
}

void MapBox::setCamera(Entity * c) {
  camera = c;
  layer = c->getLayer();
}

Entity * MapBox::getCamera() {
  return camera;
}

void MapBox::addWidget(QWidget * w) {
  mapScene->addWidget(w);
}

MapScene::MapScene(MapBox * m)
{
  mapBox = m;

  OutlineStyle * outlineStyle = new OutlineStyle();
  outlineStyle->setOutlineWidth(2);
  fpsLabel = new QLabel("           ");
  fpsLabel->setStyleSheet(
    "background-color: rgba(255, 255, 255, 0%);"
    "font-size: 20px;"
    "font-weight: bold;"
  );
  fpsLabel->move(5, 5);
  fpsLabel->setStyle(outlineStyle);
  addWidget(fpsLabel);

  //talkBoxTest = new TalkBox("Hello, world!\ntesting 1 2 3\nblah blah blah");
  //addItem(talkBoxTest);    
  //QStateMachine * machine = new QStateMachine;
  //QState * fadeIn = new QState(machine->rootState());
  


//   QPointF pos(10, 10);
  foreach (QGraphicsItem *item, items()) {
//     item->setFlag(QGraphicsItem::ItemIsMovable);
    item->setCacheMode(QGraphicsItem::DeviceCoordinateCache);

//     const QRectF rect = item->boundingRect();
//     item->setPos(pos.x() - rect.x(), pos.y() - rect.y());
//     pos += QPointF(0, 10 + rect.height());
  }
  
  mapPopupMenu = new QMenu();
  entityPopupMenu = new QMenu();
  
  newEntityAction = new QAction("New Entity", 0);
  deleteEntityAction = new QAction("Delete Entity", 0);
  editEntityAction = new QAction("Edit Entity", 0);

  editMapScriptsAction = new QAction("Edit Map Scripts", 0);

  mapPopupMenu->addAction(newEntityAction);
  mapPopupMenu->addAction(editMapScriptsAction);
  entityPopupMenu->addAction(newEntityAction);
  entityPopupMenu->addAction(deleteEntityAction);
  entityPopupMenu->addAction(editEntityAction);
  
  connect(newEntityAction, SIGNAL(triggered()), this, SLOT(newEntity()));
  connect(editEntityAction, SIGNAL(triggered()), this, SLOT(editEntity()));
  connect(deleteEntityAction, SIGNAL(triggered()), this, SLOT(deleteEntity()));
  connect(editMapScriptsAction, SIGNAL(triggered()), this, SLOT(editMapScripts()));

  mapFont = new QFont("Arial", 6);
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

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent * e) {
  QGraphicsScene::mousePressEvent(e);
  if(e->isAccepted()) return;

  if(mapBox->mapEditorMode == MapEditorMode::Edit && mapBox->map && e->button() == Qt::LeftButton) {
    mapBox->setTile(e);
  } else if(mapBox->mapEditorMode == MapEditorMode::Entity && 
    mapBox->map && e->button() == Qt::LeftButton) {
    mapBox->dragEntity = 
      mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
  } else if(mapBox->map && e->button() == Qt::MidButton) {
    mapBox->mouse_start_x = e->scenePos().x();
    mapBox->mouse_start_y = e->scenePos().y();
  } else if(mapBox->map && play && playerEntity && e->button() == Qt::RightButton) {
    playerEntity->clearQueue();
    playerEntity->queueMoveTo(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);

    Entity * x = mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    if(x) cprint("Entity: " + x->getName());
  } else if(mapBox->map && e->button() == Qt::RightButton) {
    Entity * x = mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    mouseScreenPos = e->screenPos();
    mouseScenePos = e->scenePos();
    if(x) {
      selectedEntity = x;
      entityPopupMenu->exec(e->screenPos());
    } else {
      mapPopupMenu->exec(e->screenPos());
    }
  }
}

void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent * e) {
  if(mapBox->map) {
    int tx, ty;
    mapBox->map->getTileSize(tx, ty);
    emit mapBox->mousePos(e->scenePos().x(), e->scenePos().y(), 
      e->scenePos().x() / tx, e->scenePos().y() / ty);
  }

  QGraphicsScene::mouseMoveEvent(e);
  if(e->isAccepted()) return;
  
  if(mapBox->mapEditorMode == MapEditorMode::Edit && mapBox->map && (e->buttons() & Qt::LeftButton) &&
     e->scenePos().x() > 0 && e->scenePos().y() > 0 && 
     e->scenePos().x() < this->width() && e->scenePos().y() < this->height()) {
    mapBox->setTile(e);
  } else if(mapBox->dragEntity && mapBox->mapEditorMode == MapEditorMode::Entity && mapBox->map && 
    (e->buttons() & Qt::LeftButton)) {
    QPointF move = e->scenePos() - e->lastScenePos();
    mapBox->dragEntity->movePos(move.x(), move.y());
  } else if(mapBox->map && (e->buttons() & Qt::MidButton)) {
    emit mapBox->setXScroll(mapBox->xo - e->scenePos().x() + mapBox->mouse_start_x);
    emit mapBox->setYScroll(mapBox->yo - e->scenePos().y() + mapBox->mouse_start_y);
    mapBox->mouse_start_x = e->scenePos().x();
    mapBox->mouse_start_y = e->scenePos().y();
  }
}

void MapScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e) {
  QGraphicsScene::mouseDoubleClickEvent(e);
  if(e->isAccepted()) return;

  if(mapBox->mapEditorMode == MapEditorMode::Entity && mapBox->map && e->button() == Qt::LeftButton) {
    Entity * x = mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    if(x) {
      emit showEntityDialog(x);
    }
  }
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * e) {
  QGraphicsScene::mouseReleaseEvent(e);
  if(e->isAccepted()) return;

  if((e->buttons() & Qt::LeftButton)) mapBox->dragEntity = 0;
}

void MapScene::keyEvent(int key, int eventType) {
  switch(key) {
    case Qt::Key_Up:
      input->up = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_Down:
      input->down = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_Left:
      input->left = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_Right:
      input->right = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_Enter:
      input->ok = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_Escape:
      input->cancel = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_Space:
      input->action = (eventType == QEvent::KeyPress);
      break;
    case Qt::Key_F5:
      if(eventType == QEvent::KeyPress) console->clear();
      break;
    case Qt::Key_QuoteLeft:
      input->console = (eventType == QEvent::KeyPress);
      break;
  }
}

void MapScene::keyPressEvent(QKeyEvent * event) {
  //cprint("Key Press");
  QGraphicsScene::keyPressEvent(event);
  if(event->isAccepted()) return;
  
  keyEvent(event->key(), QEvent::KeyPress);
}

void MapScene::keyReleaseEvent(QKeyEvent * event) {
  //cprint("Key Release");
  QGraphicsScene::keyPressEvent(event);
  if(event->isAccepted()) return;

  keyEvent(event->key(), QEvent::KeyRelease);
}

void MapBox::setX(int x) {
  //makeCurrent();
  xo = x;

  if(xo < 0) xo = 0;
  if(xo >= xrange) xo = xrange - 1;
  //updateGL();
  update();
}

void MapBox::setY(int y) {
  //makeCurrent();
  yo = y;

  if(yo < 0) yo = 0;
  if(yo >= yrange) yo = yrange - 1;
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
  if(layer >= 0 && layer < map->getLayers()) {
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
    emit setLayerRange(0, map->getLayers() - 1);
    if(map->getLayers() == 1) {
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
  if(map->getLayers() < layer) layer = map->getLayers();
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

    if(map->getLayers() == 0) {
      emit setLayerRange(0, 0);
    } else {
      emit setLayerRange(0, map->getLayers() - 1);
    }

    RPGEngine::setCurrentMap(map);

    QScriptValue objectValue = scriptEngine->newQObject(map);
    scriptEngine->globalObject().setProperty("map", objectValue);
  } else {
    scriptEngine->globalObject().setProperty("map", QScriptValue(QScriptValue::NullValue));
  }
  
}

void MapScene::init(int w, int h)
{
  glViewport(0, 0, (GLdouble) w, (GLdouble) h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, (GLdouble) w, (GLdouble) h, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
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

Entity * MapBox::entityAt(int x, int y) {
  if(map && map->getLayers() > 0) {
    double x1, y1, x2, y2;
    if(play) {
      // Count down from the top, so we know we'll get the ones on top first.
      for(int i = map->getEntities(layer) - 1; i >= 0; i--) {
        map->getEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) return map->getEntity(layer, i);
      }
    } else {
      for(int i = map->getStartEntities(layer) - 1; i >= 0; i--) {
        map->getStartEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) return map->getStartEntity(layer, i);
      }
    }
  }
  return 0;
}

QList < Entity * > MapBox::entitiesAt(int x, int y) {
  QList < Entity *> entities;

  if(map && map->getLayers() > 0) {
    double x1, y1, x2, y2;
    if(play) {
      // Count down from the top, so we know we'll get the ones on top first.
      for(int i = map->getEntities(layer) - 1; i >= 0; i--) {
        map->getEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) entities.append(map->getEntity(layer, i));
      }
    } else {
      for(int i = map->getStartEntities(layer) - 1; i >= 0; i--) {
        map->getStartEntity(layer, i)->getRealSpriteBox(x1, y1, x2, y2);
        if(x >= x1 && x <= x2 && y >= y1 && y <= y2) entities.append(map->getStartEntity(layer, i));
      }
    }
  }

  return entities;
}

LayerView::LayerViewMode MapBox::getDrawMode() {
  return drawMode;
}
  
void MapScene::drawBackground(QPainter *painter, const QRectF &) {
  /*
  if (painter->paintEngine()->type() != QPaintEngine::OpenGL) {
    qWarning("OpenGLScene: drawBackground needs a QGLWidget to be set as viewport on the graphics view");
    return;
  }
  */
  if(frames == 0) init(screen_x, screen_y);
  frames++;
  painter->save();
  painter->setPen(QColor(255, 255, 255));
  painter->setFont(*mapFont);
  
  // GAME ENGINE LOOP
  if(play) {
    setFocus();
    framesThisSecond++;

    /*
    if(input->up) mapBox->Move(0, -1);
    if(input->down) mapBox->Move(0, 1);
    if(input->left) mapBox->Move(-1, 0);
    if(input->right) mapBox->Move(1, 0);
    */
    if(input->action) playerEntity->setActivated(true);
    if(input->console) {
      console->setVisible(!(console->isVisible()));
      input->console = false;
    }
    if(mapBox->map) mapBox->map->update();
    
    playerEntity->setActivated(false);

    if(mapBox->getCamera()) {
      mapBox->setX(mapBox->getCamera()->getX() - screen_x / 2);
      mapBox->setY(mapBox->getCamera()->getY() - screen_y / 2);
    }
    
    // TODO: make this handle pauses
    int e = apptime.elapsed();
    timeSinceLastFrame = e - timeLastFrame;
    timeLastFrame = e;
    
    if(fpstime.elapsed() >= 1000) {
      /*fpsLabel->setText(QString("%1 %4 (%2, %3)") 
        .arg(framesThisSecond).arg(mapBox->xo).arg(mapBox->yo).arg(mapBox->GetMap()->GetName())); */
      fpsLabel->setText(QString::number(framesThisSecond));
      framesThisSecond = 0;
      fpstime.restart();
    }
    fpsLabel->repaint();
  }

  int i;
  
  /*
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, 640, 480, 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  */
  glPushMatrix();

  glViewport(0, 0, width(), height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width(), height(), 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glDisable(GL_LIGHTING);
  glClearColor( 0.5, 0.5, 0.5, 1.0 ); 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  if(mapBox->map) {
    int tw, th;
    int xrange, yrange;
    
    mapBox->map->getTileSize(tw, th);
    mapBox->map->getSize(mapBox->layer, xrange, yrange);
    xrange = xrange * tw - width();
    yrange = yrange * th - height();

    painter->beginNativePainting();

    for(i = 0; i < mapBox->map->getLayers(); i++) {
      if(i == mapBox->layer) {
        mapBox->map->draw(i, mapBox->xo, mapBox->yo, 1.0);
      } else if(mapBox->getDrawMode() == LayerView::All || 
                mapBox->getDrawMode() == LayerView::AllBelow ||
                mapBox->getDrawMode() == LayerView::AllOpaque ) {
        double opacity = 1.0;
        if(i > mapBox->layer) {
          if(mapBox->getDrawMode() == LayerView::AllBelow) continue;
          if(!(mapBox->getDrawMode() == LayerView::AllOpaque)) opacity = 0.3;
        }
        
        int x, y, lw, lh;
        mapBox->map->getSize(i, lw, lh);
        lw = lw * tw - width();
        lh = lh * th - height();
        
        x = mapBox->xo * lw / xrange;
        y = mapBox->yo * lh / yrange;
        mapBox->map->draw(i, x, y, opacity);
      }
    }

    painter->endNativePainting();

    if(viewGrid) drawGrid(mapBox->layer, painter, tw, th);
    if(viewTilePos) drawNumbers(mapBox->layer, painter, tw, th);
    if(viewEntityNames) drawEntityNames(mapBox->layer, painter);
  }
  glFlush();
  glPopMatrix();
  painter->restore();
  //mapBox->repaint();
  
//#if QT_VERSION < 0x040600
  if(is_editor) QTimer::singleShot(20, this, SLOT(update()));
//#endif
}

void MapScene::editEntity() {
  Entity * x = mapBox->entityAt(mouseScenePos.x(), mouseScenePos.y());
  if(x) emit showEntityDialog(x);
}

void MapScene::editMapScripts() {
  emit showMapScriptDialog(mapBox->map);
}

void MapScene::newEntity() {
  Entity * e = new Npc("Entity " + QString::number(entities.size()));
  if(sprites.size() > 0) {
    e->setSprite(sprites[0]);
  }
  e->setPos(mouseScenePos.x(), mouseScenePos.y()); 
  e->addToMap(mapBox->layer);
  emit showEntityDialog(e);
}

void MapScene::deleteEntity() {
  delete selectedEntity;
}

void MapScene::drawGrid(int layer, QPainter * painter, int tw, int th) {
  for(int y = mapBox->yo + th - (mapBox->yo % th); y < mapBox->yo + mapBox->height(); y += th) {
    painter->drawLine(0, y - mapBox->yo, mapBox->width(), y - mapBox->yo);
  }
  for(int x = mapBox->xo + tw - (mapBox->xo % tw); x < mapBox->xo + mapBox->width(); x += tw) {
    painter->drawLine(x - mapBox->xo, 0, x - mapBox->xo, mapBox->height());
  }
}

void MapScene::drawEntityNames(int layer, QPainter * painter) {
  if(play) {
    for(int i = 0; i < mapBox->map->getEntities(layer); i++) {
      Entity * e = mapBox->map->getEntity(layer, i);
      QString t = e->getName();
      QRect r = painter->fontMetrics().boundingRect(t);
      r.moveTo(e->getX() - mapBox->xo - r.width() / 2, e->getY() - mapBox->yo);
      painter->drawText(r, Qt::AlignHCenter, t);
    }
  } else {
    for(int i = 0; i < mapBox->map->getStartEntities(layer); i++) {
      Entity * e = mapBox->map->getStartEntity(layer, i);
      QString t = e->getName();
      QRect r = painter->fontMetrics().boundingRect(t);
      r.moveTo(e->getX() - mapBox->xo - r.width() / 2, e->getY() - mapBox->yo);
      painter->drawText(r, Qt::AlignHCenter, t);
    }
  }
}

void MapScene::drawNumbers(int layer, QPainter * painter, int tw, int th) {
  // Draw the tile x, y position on each tile
  for(int y = mapBox->yo - (mapBox->yo % th); y < mapBox->yo + mapBox->height(); y += th) {
    for(int x = mapBox->xo - (mapBox->xo % tw); x < mapBox->xo + mapBox->width(); x += tw) {
      QString posText = QString::number(x / tw) + ", " + QString::number(y / th) + "\n" + QString::number(mapBox->map->getTile(layer, x / tw, y / th));
      painter->drawText(QRectF(x - mapBox->xo + 1, y - mapBox->yo + 1, tw - 1, th - 1), posText);
    }
  }
}
