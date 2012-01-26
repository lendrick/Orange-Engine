#include "mapbox.h"
#include "bitmap.h"
#include "tileselect.h"
#include "map.h"

#include <QtOpenGL>
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
#include "scriptutils.h"

using std::cout;

MapScene::MapScene(MapBox * m)
{
  mapBox = m;
  /*
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
  */

  selection = 0;
  clipboard = 0;

  drawingSelectBox = false;
  movingSelectBox = false;
  mouseStartX = 0;
  mouseStartY = 0;
  selectBoxStartX = 0;
  selectBoxStartY = 0;

  sceneBuffer = 0;
 // bufferTexture = 0;

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

  newEntityAction = new QAction("New Entity...", 0);
  deleteEntityAction = new QAction("Delete Entity", 0);
  editEntityAction = new QAction("Edit Entity...", 0);
  editPropertiesAction = new QAction("Properties...", 0);

  editMapScriptsAction = new QAction("Edit Map Scripts...", 0);
  editGlobalScriptsAction = new QAction("Edit Global Scripts...", 0);

  mapPopupMenu->addAction(newEntityAction);
  mapPopupMenu->addAction(editMapScriptsAction);
  mapPopupMenu->addAction(editGlobalScriptsAction);

  entityPopupMenu->addAction(newEntityAction);
  entityPopupMenu->addAction(deleteEntityAction);
  entityPopupMenu->addAction(editEntityAction);
  entityPopupMenu->addAction(editPropertiesAction);

  connect(newEntityAction, SIGNAL(triggered()), this, SLOT(newEntity()));
  connect(editEntityAction, SIGNAL(triggered()), this, SLOT(editEntity()));
  connect(deleteEntityAction, SIGNAL(triggered()), this, SLOT(deleteEntity()));
  connect(editMapScriptsAction, SIGNAL(triggered()), this, SLOT(editMapScripts()));
  connect(editGlobalScriptsAction, SIGNAL(triggered()), this, SLOT(editGlobalScripts()));
  connect(editPropertiesAction, SIGNAL(triggered()), this, SLOT(editProperties()));

  mapFont = new QFont("Arial", 6);
  entityFont = new QFont("Arial", 12);

  selectedEntity = EntityPointer();

  mapBox->rootContext()->setContextProperty("scene", this);



}

void MapScene::init(int w, int h)
{
  /*
  glViewport(0, 0, (GLdouble) w, (GLdouble) h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  gluOrtho2D(0, (GLdouble) w, (GLdouble) h, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  */

}

void MapScene::setSceneRect(const QRectF &rect) {
  QGraphicsScene::setSceneRect(rect);

  qDebug() << "Scene resize to " << rect;

  if(sceneBuffer) {
    delete sceneBuffer;
    sceneBuffer = 0;
  }

  static_cast<QGLWidget *>(mapBox->viewport())->makeCurrent();
  sceneBuffer = new QGLFramebufferObject(rect.size().toSize());
  blurShader = new QGLShaderProgram();

  qDebug() << "shaders: " << blurShader->shaders().length();
  if(!blurShader->addShaderFromSourceFile(QGLShader::Fragment, "shaders/mix.glsl")) {
    qDebug() << "Could not add shader: " << blurShader->log();
  }

  /*
  if(!blurShader->addShaderFromSourceFile(QGLShader::Fragment, "shaders/blur_h.glsl")) {
    qDebug() << "Could not add shader: " << blurShader->log();
  }
  */
  qDebug() << "shaders: " << blurShader->shaders().length();

  //rt_w = blurShader->uniformLocation("rtw");
  //rt_h = blurShader->uniformLocation("rth");
  //blurShader->setUniformValue(rt_w, (GLint) rect.width());
  //blurShader->setUniformValue(rt_h, (GLint) rect.height());

  qDebug() << "BLURSHADER ADD: " << blurShader->log();

  if(!blurShader->link()) {
    qDebug() << "Could not link shader: " << blurShader->log();
  }

  blurShader->setUniformValue("source", sceneBuffer->texture());
  blurShader->setUniformValue("ratio", (GLfloat) 0.5);


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

    if(input->menu) {
      emit menuKey();
      input->menu = false;
    }
    if(input->action) playerEntity->setActivated(true);
    if(input->console) {
      console->setVisible(!(console->isVisible()));
      input->console = false;
    }

    if(rpgEngineStarting) {
      scriptUtils->include("scripts/startup.js");
    }

    // Global scripts.
    for(int i = 0; i < globalScripts.size(); i++) {
      bool execute = false;
      RPGScript * s = &(globalScripts[i]);
      if(rpgEngineStarting && s->condition == ScriptCondition::Load) {
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
    //fpsLabel->repaint();
    input->action = false;
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

  /*
  glViewport(0, 0, width(), height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width(), height(), 0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  */

  glDisable(GL_LIGHTING);
  glClearColor( 0.5, 0.5, 0.5, 1.0 );
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


  if(mapBox->map && mapBox->map->getLayerCount() > 0) {
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
    sceneBuffer->bind();
    glDisable(GL_LIGHTING);
    glClearColor( 0.5, 0.5, 0.5, 1.0 );
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, thisWidth, thisHeight, 0);
    */

    for(i = 0; i < mapBox->map->getLayerCount(); i++) {
      //message("drawing layer " + QString::number(i));
      if(i == mapBox->layer) {
        // Draw the current layer
        mapBox->map->draw(i, xo, yo, 1.0, viewBoundingBoxes);
        if(selectBox.width() != 0 || selectBox.height() != 0) {
          //qDebug() << "main layer " << xo << " " << yo;
          drawFloatingLayer(selection, selectBox, xo, yo, tw, th);
        }
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
    sceneBuffer->release();
    //static_cast<QGLWidget *>(mapBox->viewport())->makeCurrent();
    //glPopMatrix();

    //sceneBuffer->toImage().save("/home/bart/testimg.png");
    //sceneBuffer->updateDynamicTexture(sceneBuffer->texture());
/*
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, thisWidth, thisHeight, 0);
*/
   // glEnable(GL_FRAGMENT_PROGRAM_ARB);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, sceneBuffer->texture());
    glEnable(GL_BLEND);   // Turn Blending On
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFunc(GL_ONE, GL_ZERO);
    glColor4f(1.0, 1.0, 1.0, 1);


    //blurShader->setUniformValue("ratio", (GLfloat) 0.5);
    //blurShader->setUniformValue("source", (GLfloat) sceneBuffer->texture());

    blurShader->bind();
    //blurShader->setUniformValue(rt_h, (GLfloat) 480);
    //blurShader->setUniformValue(rt_w, (GLfloat) 640);
    blurShader->setUniformValue("ratio", (GLfloat) 1);
    blurShader->setUniformValue("source", (GLfloat) sceneBuffer->texture());


    glBegin(GL_QUADS);
    glTexCoord2f(0, 1); glVertex3f(0, 0, 0);
    glTexCoord2f(0, 0); glVertex3f(0, thisHeight, 0);
    glTexCoord2f(1, 0); glVertex3f(thisWidth, thisHeight, 0);
    glTexCoord2f(1, 1); glVertex3f(thisWidth, 0, 0);
    glEnd();
  //  blurShader->release();

//    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    blurShader->release();

    painter->endNativePainting();

    if(viewGrid) drawGrid(mapBox->layer, painter, tw, th);
    if(viewTilePos) drawNumbers(mapBox->layer, painter, tw, th);
    if(viewEntityNames) drawEntityNames(mapBox->layer, painter);

    if(selectBox.width() != 0 || selectBox.height() != 0) {
      drawSelectBox(mapBox->layer, painter, tw, th);
    }

    if(mapBox->mapEditorMode == MapEditorMode::Edit && !play)
      drawTileHighlight(painter, tw, th);
    //if(viewBoundingBoxes) drawEntityBoundingBoxes(mapBox->layer, painter);
  }
  glFlush();
  glPopMatrix();
  painter->restore();
  //mapBox->repaint();


//#if QT_VERSION < 0x040600
  //if(is_editor) QTimer::singleShot(20, this, SLOT(update()));
  update(this->sceneRect());
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

void MapScene::editProperties() {
  if(selectedEntity) {
    emit showPropertyEditor(selectedEntity);
  }
}

void MapScene::editMapScripts() {
  emit showMapScriptDialog(mapBox->map);
}

void MapScene::editGlobalScripts() {
  emit showGlobalScriptDialog();
}

void MapScene::newEntity() {
  int x = entities.size();
  while(staticEntityNames.contains("Entity " + QString::number(x))) {
    x++;
  }

  Entity * ePtr;

  try {
    ePtr = new Npc("Entity " + QString::number(x));
  } catch(QString s) {
    QMessageBox::warning(0, "Error", s);
    return;
  }

  EntityPointer e = ePtr->getSharedPointer();

  /*
  if(sprites.size() > 0) {
    e->setSprite(sprites[0]);
  }
  */
  e->setSprite(0);
  e->setPos(mouseScenePos.x(), mouseScenePos.y());
  e->addToMap(mapBox->layer);
  emit showEntityDialog(e);
}

void MapScene::deleteEntity() {
  selectedEntity->destroy();
}

void MapScene::drawGrid(int layer, QPainter * painter, int tw, int th) {
  for(int y = mapBox->yo + th - (mapBox->yo % th); y < mapBox->yo + mapBox->height(); y += th) {
    painter->drawLine(0, y - mapBox->yo, mapBox->width(), y - mapBox->yo);
  }
  for(int x = mapBox->xo + tw - (mapBox->xo % tw); x < mapBox->xo + mapBox->width(); x += tw) {
    painter->drawLine(x - mapBox->xo, 0, x - mapBox->xo, mapBox->height());
  }
}

void MapScene::drawSelectBox(int layer, QPainter * painter, int tw, int th) {
  int x, y, w, h;
  painter->save();

  QPen selectPen(Qt::DashLine);
  selectPen.setColor(Qt::white);
  selectPen.setWidth(2);

  x = selectBox.x() * tw - mapBox->xo;
  y = selectBox.y() * th - mapBox->yo;
  w = selectBox.width() * tw;
  h = selectBox.height() * th;
  painter->setPen(selectPen);
  painter->drawRect(x, y, w, h);
  painter->restore();
}

void MapScene::drawTileHighlight(QPainter * painter, int tw, int th) {
  int x, y;
  getMouseTileCoords(x, y);

  if(x >= 0 && y >= 0) {
    painter->fillRect(x * tw - mapBox->xo, y * th - mapBox->yo, tw, th, QColor(255, 255, 255, 50));
  }
}

void MapScene::drawFloatingLayer(Map::Layer * layer, QRect rect, int xo, int yo, int tw, int th) {
  //qDebug() << "drawing floating layer";
  int x, y;

  x = rect.x() * tw - xo;
  y = rect.y() * th - yo;

  //qDebug() << x << " " << y;

  mapBox->map->draw(layer, -x, -y, 1, false, false);
}

void MapScene::drawEntityNames(int layer, QPainter * painter) {
  painter->save();
  painter->setFont(*entityFont);

  int count;
  if(play)
    count = mapBox->map->getEntityCount(layer);
  else
    count = mapBox->map->getStartEntityCount(layer);
  EntityPointer e = EntityPointer();

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

void MapScene::mousePressEvent(QGraphicsSceneMouseEvent * e) {
  //qDebug() << "MapScene::mousePressEvent";
  //setFocus(Qt::MouseFocusReason);
  QGraphicsScene::mousePressEvent(e);
  if(e->isAccepted()) return;
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

  drawingSelectBox = false;
  movingSelectBox = false;
  mouseStartX = e->scenePos().x();
  mouseStartY = e->scenePos().y();
  e->accept();

  if(mapBox->mapEditorMode == MapEditorMode::Edit && mapBox->map && e->button() == Qt::LeftButton) {
    if(paintMode == PaintMode::Draw && !play) {
      mapBox->setTile(e);
    } else if(paintMode == PaintMode::SelectBox) {
      if(mouseInsideSelection(e)) {
        movingSelectBox = true;
        selectBoxStartX = selectBox.x();
        selectBoxStartY = selectBox.y();
      } else {
        drawingSelectBox = true;
        //qDebug() << "MouseClick: " << e;
        if(selection) {
          selection->stamp(mapBox->getCurrentLayer(),selectBox.x(), selectBox.y());
          delete selection;
          selection = 0;
        }

        selectBox = QRect();

        int w, h, x, y;

        mapBox->map->getTileSize(w, h);
        x = (mapBox->xo + mouseStartX) / w;
        y = (mapBox->yo + mouseStartY) / h;

        selectBox.setX(x);
        selectBox.setY(y);
        selectBox.setWidth(0);
        selectBox.setHeight(0);

        //qDebug() << selectBox;
      }
    } else if(paintMode == PaintMode::Brush) {

    } else if(paintMode == PaintMode::Fill) {
      int w, h, x, y;

      mapBox->map->getTileSize(w, h);
      x = (mapBox->xo + mouseStartX) / w;
      y = (mapBox->yo + mouseStartY) / h;
      fill(mapBox->layer, x, y, mapBox->currentTile);
    }
    //qDebug() << "  set tile";
  } else if(mapBox->mapEditorMode == MapEditorMode::Entity &&
    mapBox->map && e->button() == Qt::LeftButton) {
    int mouseX = mouseStartX + mapBox->xo;
    int mouseY = mouseStartY + mapBox->yo;
    mapBox->dragEntity = mapBox->entityAt(mouseX, mouseY);
    if(mapBox->dragEntity) {
      mapBox->resizeDirection = mapBox->edgeAt(mapBox->dragEntity, mouseX, mouseY);
      /*
      double x1, y1, x2, y2;
      mapBox->dragEntity->getRealSpriteBox(x1, y1, x2, y2);
      if(mouseX >= x1 && mouseX <= x1 + 2) {
        mapBox->resizeDirection |= Direction::Left;
      } else if(mouseX >= x2 - 2 && mouseX <= x2) {
        mapBox->resizeDirection |= Direction::Right;
      }
      if(mouseY >= y1 && mouseY <= y1 + 2) {
        mapBox->resizeDirection |= Direction::Up;
      } else if(mouseY >= y2 - 2 && mouseY <= y2) {
        mapBox->resizeDirection |= Direction::Down;
      }
      */
      if(mapBox->resizeDirection != Direction::None) {
        mapBox->dragMode = DragMode::Resize;
      } else {
        mapBox->dragMode = DragMode::Drag;
      }
    }
    //qDebug() << "  starting drag " << mapBox->dragEntity->getName().toAscii().data();
  } else if(mapBox->map && e->button() == Qt::MidButton) {
    mapBox->mouse_start_x = mouseStartX;
    mapBox->mouse_start_y = mouseStartY;
    //qDebug() << "  middle button pressed";
  } else if(mapBox->map && play && playerEntity && e->button() == Qt::RightButton) {
    playerEntity->clearQueue();
    playerEntity->queueMoveTo(mouseStartX + mapBox->xo, mouseStartY + mapBox->yo);

    EntityPointer x = mapBox->entityAt(mouseStartX + mapBox->xo, mouseStartY + mapBox->yo);
    if(x) cprint("Entity: " + x->getName());
    //qDebug() << "  right button pressed in play mode";
  } else if(mapBox->map && e->button() == Qt::RightButton) {
    EntityPointer x = mapBox->entityAt(mouseStartX + mapBox->xo, mouseStartY + mapBox->yo);
    mouseScreenPos = e->screenPos();
    mouseScenePos = e->scenePos() + QPoint(mapBox->xo, mapBox->yo);
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
    e->ignore();
  }
  //qDebug() << "  accepted";

}

void MapScene::mouseMoveEvent(QGraphicsSceneMouseEvent * e) {
  //qDebug() << "MapScene::mouseMoveEvent";

  if(mapBox->map) {
    int tx, ty;
    mapBox->map->getTileSize(tx, ty);
    //emit mapBox->mousePos(e->scenePos().x(), e->scenePos().y(),
    //  e->scenePos().x() / tx, e->scenePos().y() / ty);
    if(!play) {
      int x = (mapBox->xo + e->scenePos().x());
      int y = (mapBox->yo + e->scenePos().y());
      emit statusMessage(QString::number(x / tx) + ", " + QString::number(y / ty) +
                         "  (" + QString::number(x) + ", " + QString::number(y) + ") " + QString::number(mapBox->xo) + ", " + QString::number(mapBox->yo));
    }
  }




  QGraphicsScene::mouseMoveEvent(e);
  if(e->isAccepted()) return;
  //cout << e->buttons() << "\n";
  if(e->buttons()) {
    e->accept();
    if(mapBox->mapEditorMode == MapEditorMode::Edit && mapBox->map && (e->buttons() & Qt::LeftButton) &&
       e->scenePos().x() > 0 && e->scenePos().y() > 0 &&
       e->scenePos().x() < this->width() && e->scenePos().y() < this->height()) {
      if(paintMode == PaintMode::Draw && !play) {
        mapBox->setTile(e);
      } else if(paintMode == PaintMode::SelectBox) {
        int w, h, x, y;
        mapBox->map->getTileSize(w, h);

        if(movingSelectBox) {
          selectBox.moveTo(selectBoxStartX + (e->scenePos().x() - mouseStartX) / w,
                           selectBoxStartY + (e->scenePos().y() - mouseStartY) / h);
        } else if(drawingSelectBox) {
          //qDebug() << "MouseMove: " << e;
          mapBox->map->getTileSize(w, h);
          x = (mapBox->xo + e->scenePos().x()) / w;
          y = (mapBox->yo + e->scenePos().y()) / h;

          int width, height;
          width = x - selectBox.x();
          height = y - selectBox.y();

          if(width >= 0) width++;
          if(height >= 0) height++;
          selectBox.setWidth(width);
          selectBox.setHeight(height);
        }
      } else if(paintMode == PaintMode::Brush) {

      } else if(paintMode == PaintMode::Fill) {
        // Don't actually do anything if the mouse is dragged in fill mode
      }

      //qDebug() << "  setTile";
    } else if(mapBox->mapEditorMode == MapEditorMode::Entity && mapBox->map) {
      if(mapBox->dragEntity && mapBox->dragMode == DragMode::Drag && (e->buttons() & Qt::LeftButton)) {
        QPointF move = e->scenePos() - e->lastScenePos();
        //qDebug() << "  dragging " << move.x() << " " << move.y() << "\n";
        mapBox->dragEntity->movePos(move.x(), move.y());
      } else if((e->buttons() & Qt::LeftButton) && mapBox->dragMode == DragMode::Resize && mapBox->dragEntity) {
        QPointF move = e->scenePos() - e->lastScenePos();
        int x1, y1, x2, y2;
        mapBox->dragEntity->getBoundingBox(x1, y1, x2, y2);

        if(mapBox->resizeDirection & Direction::Up) {
          y1 += move.y();
        }

        if(mapBox->resizeDirection & Direction::Down) {
          y2 += move.y();
        }

        if(mapBox->resizeDirection & Direction::Left) {
          x1 += move.x();
        }

        if(mapBox->resizeDirection & Direction::Right) {
          x2 += move.x();
        }

        mapBox->dragEntity->setBoundingBox(x1, y1, x2, y2);
      }
    } else if(mapBox->map && (e->buttons() & Qt::MidButton)) {
      emit mapBox->setXScroll(mapBox->xo - e->scenePos().x() + mapBox->mouse_start_x);
      emit mapBox->setYScroll(mapBox->yo - e->scenePos().y() + mapBox->mouse_start_y);
      mapBox->mouse_start_x = e->scenePos().x();
      mapBox->mouse_start_y = e->scenePos().y();
      //qDebug() << "  scroll";
    } else {
      //qDebug() << "  not handled";
      e->ignore();
      return;
    }
  } else if(mapBox->mapEditorMode == MapEditorMode::Entity) {
    QCursor oc;
    // Adjust the mouse cursor if hovering
    int x = (mapBox->xo + e->scenePos().x());
    int y = (mapBox->yo + e->scenePos().y());
    EntityPointer p = mapBox->entityAt(x, y);
    if(QApplication::overrideCursor())
      QApplication::restoreOverrideCursor();
    if(p) {
      int edge = mapBox->edgeAt(p, x, y);
      if(edge == Direction::Up) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
      } else if(edge == Direction::Down) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeVerCursor));
      } else if(edge == Direction::Left) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
      } else if(edge == Direction::Right) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeHorCursor));
      } else if(edge == Direction::UpLeft) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
      } else if(edge == Direction::DownLeft) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
      } else if(edge == Direction::UpRight) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeBDiagCursor));
      } else if(edge == Direction::DownRight) {
        QApplication::setOverrideCursor(QCursor(Qt::SizeFDiagCursor));
      } else {
        QApplication::setOverrideCursor(QCursor(Qt::PointingHandCursor));
      }
    }
  }
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
    EntityPointer x = mapBox->entityAt(e->scenePos().x() + mapBox->xo, e->scenePos().y() + mapBox->yo);
    if(x) {
      emit showEntityDialog(x);
      e->accept();
    }
  }
}

void MapScene::mouseReleaseEvent(QGraphicsSceneMouseEvent * e) {
  QGraphicsScene::mouseReleaseEvent(e);

  if(e->isAccepted()) return;

  //qDebug() << "MapScene::mouseReleaseEvent " << e->buttons();
  //QGraphicsScene::mouseReleaseEvent(e);
  //if(e->isAccepted()) return;
  e->accept();
  if(drawingSelectBox) {
    if(paintMode == PaintMode::SelectBox) {
      if(!selection) {
        qDebug() << "selection released " << selectBox;
        updateSelection();
      }
    } else {
      qDebug() << "WARNING: drawingSelectBox true while not in PaintMode::SelectBox";
    }/*else {
      mapBox->dragEntity = EntityPointer();
      e->accept();
    }*/
    return;
  } else {
    e->ignore();
  }
  drawingSelectBox = false;
  movingSelectBox = false;
  mouseStartX = 0;
  mouseStartY = 0;

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
    case Qt::Key_Tab:
      input->menu = (eventType == QEvent::KeyPress);
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

void MapScene::fill(int layer, int x, int y, int tile, int firstTile)  {
  int w, h;
  mapBox->map->getSize(layer, w, h);
  if(x < 0 || y < 0 || x >= w || y >= h) {
    return;
  }

  /*  int x1, y1, x2, y2;
  x1 = selectBox.x();
  y1 = selectBox.y();
  x2 = x1 + selectBox.width();
  y2 = y1 + selectBox.height();

  if(x2 < x1) std::swap(x1, x2);
  if(y2 < y1) std::swap(y1, y2);

  if((selectBox.width() != 0 || selectBox.height != 0) &&
     (x < x1 || y < x1 || x > select))
  */

  if((selectBox.width() != 0 && selectBox.height() != 0) &&
     (!(selectBox.contains(x, y, false)))) {
    return;
  }

  if(firstTile == -1) {
    firstTile = mapBox->map->getTile(layer, x, y);
  }

  if(tile == firstTile) return;

  if(mapBox->map->getTile(layer, x, y) == firstTile) {
    mapBox->map->setTile(layer, x, y, tile);
    fill(layer, x + 1, y, tile, firstTile);
    fill(layer, x - 1, y, tile, firstTile);
    fill(layer, x, y + 1, tile, firstTile);
    fill(layer, x, y - 1, tile, firstTile);
  }
}

bool MapScene::mouseInsideSelection(QGraphicsSceneMouseEvent * e) {
  if(!selection || drawingSelectBox)
    return false;

  int w, h, x, y;

  mapBox->map->getTileSize(w, h);
  x = (mapBox->xo + e->scenePos().x()) / w;
  y = (mapBox->yo + e->scenePos().y()) / h;

  if(selectBox.contains(x, y, false))
    return true;
  else
    return false;
}

void MapScene::cutSelection() {
  copySelection();
  selection->clear();
  selectBox = QRect();
}

void MapScene::pasteSelection() {
  if(selection) {
    selection->stamp(mapBox->getCurrentLayer(), selectBox.x(), selectBox.y());

    delete selection;
    selection = 0;
  }

  int x, y;
  getMouseTileCoords(x, y);

  if(x == -1) x = 0;
  if(y == -1) y = 0;

  selection = new Map::Layer(clipboard);
  selectBox = QRect(x, y, selection->width, selection->height);
}

void MapScene::deleteSelection() {
  selection->clear();
}

void MapScene::copySelection() {
  if(clipboard) {
    delete clipboard;
    clipboard = 0;
  }

  clipboard = new Map::Layer(selection);
}

void MapScene::selectAll() {
  int w, h;
  mapBox->map->getSize(mapBox->layer, w, h);
  selectBox = QRect(0, 0, w, h);
  updateSelection();
}

void MapScene::selectNone() {
  selectBox = QRect();
  if(selection) {
    delete selection;
    selection = 0;
  }
}

void MapScene::updateSelection() {
  if(selection) {
    delete selection;
    selection = 0;
  }

  // You would think this would work, but it actually results in a rectangle that's one step
  // too large on each side:
  //selectBox = selectBox.normalized();

  if(selectBox.width() < 0) {
    int w = selectBox.width();
    int x = selectBox.x();

    selectBox.moveLeft(x + w);
    selectBox.setWidth(-w);
  }

  if(selectBox.height() < 0) {
    int h = selectBox.height();
    int y = selectBox.y();

    selectBox.moveTop(y + h);
    selectBox.setHeight(-h);
  }


  //qDebug() << "Normalized: " << selectBox;
  Map::Layer * currentLayer = mapBox->getCurrentLayer();
  selection = new Map::Layer(currentLayer,
                        selectBox.x(), selectBox.y(),
                        selectBox.width(), selectBox.height());
  currentLayer->fillArea(selectBox.x(), selectBox.y(),
                         selectBox.width(), selectBox.height(), 0);
  //selection->dump();
}

void MapScene::getMouseTileCoords(int &x, int &y) {
  int tw, th;
  mapBox->map->getTileSize(tw, th);
  QPoint p = mapBox->mapFromGlobal(QCursor::pos());

  //qDebug() << p << " " << mapBox->xo << " " << mapBox->yo << "(" << tw << " " << th << ")";
  x = (p.x() + mapBox->xo) / tw;
  y = (p.y() + mapBox->yo) / th;

  if(x < 0 || x >= mapBox->getCurrentLayer()->width ||
     y < 0 || y >= mapBox->getCurrentLayer()->height) {
    x = -1;
    y = -1;
  }
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

void MapScene::addItem(QGraphicsItem *item) {
  QGraphicsScene::addItem(item);
}
