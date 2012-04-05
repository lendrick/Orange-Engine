#ifndef QMLMAPWIDGET_H
#define QMLMAPWIDGET_H

#include <QDeclarativeItem>
#include <QtOpenGL>
#include <QtGui>
#include <QGraphicsSceneMouseEvent>
#include "map.h"
#include "globals.h"
#include "entity.h"

class MapScene;
class Map;

class QmlMapWidget : public QDeclarativeItem {
    Q_OBJECT
    Q_PROPERTY(int width READ width)
    Q_PROPERTY(int height READ height)

    friend class MapScene;



  public:
    QmlMapWidget(QDeclarativeItem * parent=0);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
    void init(int w, int h);
    void drawGrid(int layer, QPainter *painter, int tw, int th);
    void drawEntityNames(int layer, QPainter *painter);
    void drawNumbers(int layer, QPainter *painter, int tw, int th);
    void drawSelectBox(int layer, QPainter *painter, int tw, int th);
    void drawTileHighlight(QPainter *painter, int tw, int th);
    void drawFloatingLayer(Map::Layer * layer, QRect rect, int xo, int yo, int tw, int th);
    void getMouseTileCoords(int &x, int &y);

    void mousePressEvent(QGraphicsSceneMouseEvent * e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * e);
    void mouseMoveEvent(QGraphicsSceneMouseEvent * e);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent * e);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);
    void keyEvent(int key, int eventType);
    void updateSelection();


    MapScene * mapScene;
    QPoint mouseScreenPos;
    QPointF mouseScenePos;
    QFont * mapFont;
    QFont * entityFont;
    QRect selectBox;

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
    void setCamera(EntityPointer);
    EntityPointer getCamera();
    void setDrawMode(LayerView::LayerViewMode);
    void setCurrentTile(int);
    EntityPointer entityAt(int x, int y);
    int edgeAt(EntityPointer entity, int x, int y);
    QList < EntityPointer > entitiesAt(int x, int y);
    Map::Layer * getCurrentLayer();

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
    void resized(int, int);

  private:
    void setTile(QMouseEvent * e);
    void setTile(QGraphicsSceneMouseEvent * e);

    Map * map;
    int xo, yo;
    int layer;
    int mouse_start_x, mouse_start_y;
    LayerView::LayerViewMode drawMode;
    int currentTile;
    int xrange, yrange;
    EntityPointer camera;
    EntityPointer dragEntity;
    int resizeDirection;
    int mapEditorMode;
    int dragMode;
};

#endif // QMLMAPWIDGET_H
