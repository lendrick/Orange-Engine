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

#include <QtCore>
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

MapScene::MapScene(MapBox * m)
{
  mapBox = m;

  OutlineStyle * outlineStyle = new OutlineStyle();
  outlineStyle->setOutlineWidth(2);
  fpsLabel = new QLabel("                                          ");
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
  editGlobalScriptsAction = new QAction("Edit Global Scripts", 0);

  mapPopupMenu->addAction(newEntityAction);
  mapPopupMenu->addAction(editMapScriptsAction);
  mapPopupMenu->addAction(editGlobalScriptsAction);

  entityPopupMenu->addAction(newEntityAction);
  entityPopupMenu->addAction(deleteEntityAction);
  entityPopupMenu->addAction(editEntityAction);

  connect(newEntityAction, SIGNAL(triggered()), this, SLOT(newEntity()));
  connect(editEntityAction, SIGNAL(triggered()), this, SLOT(editEntity()));
  connect(deleteEntityAction, SIGNAL(triggered()), this, SLOT(deleteEntity()));
  connect(editMapScriptsAction, SIGNAL(triggered()), this, SLOT(editMapScripts()));
  connect(editGlobalScriptsAction, SIGNAL(triggered()), this, SLOT(editGlobalScripts()));

  mapFont = new QFont("Arial", 6);
  entityFont = new QFont("Arial", 12);

  selectedEntity = 0;
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

    // Global scripts.
    for(int i = 0; i < globalScripts.size(); i++) {
      bool execute = false;
      RPGScript * s = &(globalScripts[i]);
      if(rpgEngineStarting && s->condition == ScriptCondition::Start) {
        execute = true;
      } else if(s->condition == ScriptCondition::EveryFrame) {
        execute = true;
      }

      if(execute) {
        scriptEngine->evaluate(s->script);

        if(scriptEngine->hasUncaughtException())
          message(scriptEngine->uncaughtException().toString());
      }
    }

    rpgEngineStarting = false;

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
      //fpsLabel->setText(QString::number(framesThisSecond) + " / " +
      //                  QString::number(mapBox->xo) + ", " + QString::number(mapBox->yo));
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
    int thisWidth, thisHeight;
    int xo, yo;

    thisWidth = width();
    thisHeight = height();

    // Get the origin of the mapbox;
    xo = mapBox->xo;
    yo = mapBox->yo;

    // Get the size of the tiles in pixels
    mapBox->map->getTileSize(tw, th);

    // Get the size of the map in tiles
    mapBox->map->getSize(mapBox->layer, xrange, yrange);

    // Calculate the range of pixels the camera can move in each direction,
    // assuming a lower bound of zero
    xrange = xrange * tw - thisWidth;
    yrange = yrange * th - thisHeight;

    painter->beginNativePainting();

    for(i = 0; i < mapBox->map->getLayerCount(); i++) {
      //message("drawing layer " + QString::number(i));
      if(i == mapBox->layer) {
        // Draw the current layer
        mapBox->map->draw(i, xo, yo, 1.0, viewBoundingBoxes);
      } else if(mapBox->getDrawMode() == LayerView::All ||
                mapBox->getDrawMode() == LayerView::AllBelow ||
                mapBox->getDrawMode() == LayerView::AllOpaque ) {
        // Draw the other layers so that they match up with the current one.
        double opacity = 1.0;
        if(i > mapBox->layer) {
          if(mapBox->getDrawMode() == LayerView::AllBelow) continue;
          if(!(mapBox->getDrawMode() == LayerView::AllOpaque)) opacity = 0.3;
        }

        int x, y, lw, lh;

        // Get the tile size of the current layer
        mapBox->map->getSize(i, lw, lh);

        // Get the pixel range of the current layer
        lw = lw * tw - thisWidth;
        lh = lh * th - thisHeight;

        // For our purposes, 0 / 0 = 1   :)
        if(xrange)
          x = xo * lw / xrange;
        else
          x = xo;

        if(yrange)
          y = yo * lh / yrange;
        else
          y = yo;

        mapBox->map->draw(i, x, y, opacity);
      }
    }

    painter->endNativePainting();

    if(viewGrid) drawGrid(mapBox->layer, painter, tw, th);
    if(viewTilePos) drawNumbers(mapBox->layer, painter, tw, th);
    if(viewEntityNames) drawEntityNames(mapBox->layer, painter);
    //if(viewBoundingBoxes) drawEntityBoundingBoxes(mapBox->layer, painter);
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
  /*
  Entity * x = mapBox->entityAt(mouseScenePos.x(), mouseScenePos.y());
  if(x)
    emit showEntityDialog(x);
  else
    message("No entity at " + QString::number(mouseScenePos.x()) + ", " +
            QString::number(mouseScenePos.y()));
            */
  if(selectedEntity)
    emit showEntityDialog(selectedEntity);
  else
    message("No entity selected.");
}

void MapScene::editMapScripts() {
  emit showMapScriptDialog(mapBox->map);
}

void MapScene::editGlobalScripts() {
  emit showGlobalScriptDialog();
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
  painter->save();
  painter->setFont(*entityFont);

  int count;
  if(play)
    count = mapBox->map->getEntityCount(layer);
  else
    count = mapBox->map->getStartEntityCount(layer);
  Entity * e = 0;

  for(int i = 0; i < count; i++) {
    if(play)
      e = mapBox->map->getEntity(layer, i);
    else
      e = mapBox->map->getStartEntity(layer, i);

    QString t = e->getName();
    QRect r = painter->fontMetrics().boundingRect(t);
    r.setWidth(painter->fontMetrics().width(t));
    r.moveTo(e->getX() - mapBox->xo - r.width() / 2, e->getY() - mapBox->yo);
    painter->drawText(r, Qt::AlignHCenter, t);
  }
  painter->restore();
}

/*
void MapScene::drawEntityBoundingBoxes(int layer, QPainter * painter) {
  int x1, y1, x2, y2, x, y;
  QBrush b(QColor(100, 100, 220, 128));
  painter->save();

  int count;
  if(play)
    count = mapBox->map->getEntityCount(layer);
  else
    count = mapBox->map->getStartEntityCount(layer);
  Entity * e = 0;

  for(int i = 0; i < count; i++) {
    if(play)
      e = mapBox->map->getEntity(layer, i);
    else
      e = mapBox->map->getStartEntity(layer, i);

    x = e->getX();
    y = e->getY();
    e->getBoundingBox(x1, y1, x2, y2);
    //qDebug() << e->getName() << (x1 + x - mapBox->xo) << " " << (y1 + y - mapBox->yo) << " " << (x2 - x1) << " " << (y2 - y1);
    painter->fillRect(x1 + x - mapBox->xo, y1 + y - mapBox->yo, x2-x1, y2-y1, b);
  }
  painter->restore();
}
*/

void MapScene::drawNumbers(int layer, QPainter * painter, int tw, int th) {
  // Draw the tile x, y position on each tile
  for(int y = mapBox->yo - (mapBox->yo % th); y < mapBox->yo + mapBox->height(); y += th) {
    for(int x = mapBox->xo - (mapBox->xo % tw); x < mapBox->xo + mapBox->width(); x += tw) {
      QString posText = QString::number(x / tw) + ", " + QString::number(y / th) + "\n" + QString::number(mapBox->map->getTile(layer, x / tw, y / th));
      painter->drawText(QRectF(x - mapBox->xo + 1, y - mapBox->yo + 1, tw - 1, th - 1), posText);
    }
  }
}

void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent * e) {
  //qDebug() << "MapScene::mouseMoveEvent";

  if(mapBox->map) {
    int tx, ty;
    mapBox->map->getTileSize(tx, ty);
    //emit mapBox->mousePos(e->scenePos().x(), e->scenePos().y(),
    //  e->scenePos().x() / tx, e->scenePos().y() / ty);
  }


  QGraphicsScene::mouseMoveEvent(e);
  if(e->isAccepted()) return;
  //cout << e->buttons() << "\n";
  if(e->buttons()) {
    if(mapBox->mapEditorMode == MapEditorMode::Edit && mapBox->map && (e->buttons() & Qt::LeftButton) &&
       e->scenePos().x() > 0 && e->scenePos().y() > 0 &&
       e->scenePos().x() < this->width() && e->scenePos().y() < this->height()) {
      mapBox->setTile(e);
      //qDebug() << "  setTile";
    } else if(mapBox->dragEntity && mapBox->mapEditorMode == MapEditorMode::Entity && mapBox->map &&
              (e->buttons() & Qt::LeftButton)) {
      QPointF move = e->scenePos() - e->lastScenePos();
      //qDebug() << "  dragging " << move.x() << " " << move.y() << "\n";
      mapBox->dragEntity->movePos(move.x(), move.y());
    } else if(mapBox->map && (e->buttons() & Qt::MidButton)) {
      emit mapBox->setXScroll(mapBox->xo - e->scenePos().x() + mapBox->mouse_start_x);
      emit mapBox->setYScroll(mapBox->yo - e->scenePos().y() + mapBox->mouse_start_y);
      mapBox->mouse_start_x = e->scenePos().x();
      mapBox->mouse_start_y = e->scenePos().y();
      //qDebug() << "  scroll";
    } else {
      //qDebug() << "  not handled";
      return;
    }
  }
  e->accept();
  //qDebug() << "  accepted";
}
/*
void MapScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event) {
  qDebug() << "MapScene::dragMoveEvent";
  //event->accept();
  QGraphicsScene::dragMoveEvent(event);
}


void MapScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event) {
  qDebug() << "MapScene::dragEnterEvent";
  //event->accept();
  QGraphicsScene::dragEnterEvent(event);
}

void MapScene::dropEvent(QGraphicsSceneDragDropEvent *event) {
  //event->accept();
}
*/

void MapScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e) {
  //qDebug() << "MapScene::mouseDoubleClickEvent";
  QGraphicsScene::mouseDoubleClickEvent(e);
  if(e->isAccepted()) return;

  if(mapBox->mapEditorMode == MapEditorMode::Entity && mapBox->map && e->button() == Qt::LeftButton) {
    Entity * x = mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    if(x) {
      emit showEntityDialog(x);
      e->accept();
    }
  }
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * e) {
  //qDebug() << "MapScene::mouseReleaseEvent";
  //QGraphicsScene::mouseReleaseEvent(e);
  //if(e->isAccepted()) return;

  if((e->buttons() & Qt::LeftButton)) {
    mapBox->dragEntity = 0;
    e->accept();
    //qDebug() << "  left button";
    return;
  } else {
    //qDebug() << "  not accepted";
  }

  QGraphicsScene::mouseReleaseEvent(e);
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

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent * e) {
  //qDebug() << "MapScene::mousePressEvent";
  //setFocus(Qt::MouseFocusReason);
  //QGraphicsScene::mousePressEvent(e);
  //if(e->isAccepted()) return;
  //e->accept();
  /*
  foreach (QGraphicsItem *item, items()) {
    QGraphicsProxyWidget * gpw = dynamic_cast< QGraphicsProxyWidget *>(item);
    qDebug() << "  QGraphicsItem" << item->type();
    if(gpw) {
      //qDebug() << "  PROXYWIDGET " << mouseGrabberItem();
    }
    if(mouseGrabberItem()) {
      //qDebug() <<  "  MouseGrabber Item";
    }
    if(gpw == mouseGrabberItem()) {
      //qDebug() << "  ProxyWidget is mouse grabber";
    }
  }
  */
  if(mapBox->mapEditorMode == MapEditorMode::Edit && mapBox->map && e->button() == Qt::LeftButton) {
    mapBox->setTile(e);
    //qDebug() << "  set tile";
  } else if(mapBox->mapEditorMode == MapEditorMode::Entity &&
    mapBox->map && e->button() == Qt::LeftButton) {
    mapBox->dragEntity =
      mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    //qDebug() << "  starting drag " << mapBox->dragEntity->getName().toAscii().data();
  } else if(mapBox->map && e->button() == Qt::MidButton) {
    mapBox->mouse_start_x = e->scenePos().x();
    mapBox->mouse_start_y = e->scenePos().y();
    //qDebug() << "  middle button pressed";
  } else if(mapBox->map && play && playerEntity && e->button() == Qt::RightButton) {
    playerEntity->clearQueue();
    playerEntity->queueMoveTo(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);

    Entity * x = mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    if(x) cprint("Entity: " + x->getName());
    //qDebug() << "  right button pressed in play mode";
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
    //qDebug() << "  popup menu";
  } else {
    //qDebug() << "  unhandled";
    //return;
  }
  //qDebug() << "  accepted";
  e->accept();
}

/*
bool MapScene::event(QEvent *event)
{
  if(event->type() != 43 && event->type() != 155) {
    qDebug() << "MapScene: " << RPGEngine::eventName(event);
  }
  return QGraphicsScene::event(event);
}

bool MapScene::eventFilter(QObject * watched, QEvent * event) {
  qDebug() << "MapScene::eventFilter: " << RPGEngine::eventName(event);
  return QGraphicsScene::eventFilter(watched, event);
}
*/
