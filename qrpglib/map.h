#ifndef MAP_H
#define MAP_H 1

#include "polygon.h"
#include "bitmap.h"
#include "rpgscript.h"
#include <QtCore>

class Resource;
class Bitmap;
class Entity;
typedef QSharedPointer<Entity> EntityPointer;

class Map : public QObject, public QScriptable {
  Q_OBJECT
public:
  Map();
  Map(Bitmap * t, int x, int y, int w, int h, QString mapname = "Unnamed Map");
  ~Map();
  void draw(int layer, int x, int y, float opacity, bool boundingboxes = false);
  void getTileSize(int &w, int &h);
  void getSize(int layer, int &w, int &h);
  void setTileset(Bitmap * t);
  void setTileset(int layer, Bitmap * t);
  Bitmap * getTileset();
  void save(QString filename);
  Resource * getThisMap() { return thisMap; }
  void update();
  QScriptValue scriptObject;
  QScriptValue getScriptObject();

public slots:
  bool setName(QString n);
  QString getName();
  void setTile(int layer, int x, int y, int tile);
  int getTile(int layer, int x, int y);
  int getLayerCount();
  QString getLayerName(int layer);
  void setLayerName(int layer, QString name);
  int addLayer(int w, int h, bool wrap=false, int filltile=0, QString name = "New Layer");
  void moveLayer(int oldIndex, int newIndex);
  void insertLayerBefore(int layer, int w, int h, bool wrap=false, int filltile=0, QString name = "New Layer");
  void insertLayerAfter(int layer, int w, int h, bool wrap=false, int filltile=0, QString name = "New Layer");
  void deleteLayer(int layer);
  void setViewport(int x, int y, int w, int h);
  void addEntity(int layer, EntityPointer entity);
  void addStartEntity(int layer, EntityPointer entity);
  void removeEntity(int layer, EntityPointer entity);
  void removeStartEntity(int layer, EntityPointer entity);
  int getEntityCount(int layer);
  int getStartEntityCount(int layer);
  void reset();
  void clear();
  void setStarting(bool);
  EntityPointer getEntity(int layer, int index);
  EntityPointer getStartEntity(int layer, int index);

  void addScript(int, QString);
  void clearScripts();
  int getScriptCount() const;
  QString getScript(int) const;
  int getScriptCondition(int) const;

  //TODO
  //void SetTileset(QString tileSetName);
  //QString GetTilesetName();

private:
  int view_x, view_y, view_w, view_h;
  int tile_h, tile_w;
  QString name;

  struct Tile {
    int bitmap;
    bool solid;
    QList < Poly * > border;
    ~Tile();
  };

  QList < Tile * > tiles;

  struct Layer {
    Layer();
    ~Layer();
    int height, width;
    QString name;
    int * layerdata;
    bool wrap;
    QList < Poly * > border;
    QList < EntityPointer > entities;
    QList < EntityPointer > startEntities;
    Bitmap * tileset;
    int tile_w, tile_h;
  };

  QList < Layer * > layers;

  Bitmap * tileset;

  Resource * thisMap;
  QList < RPGScript > scripts;

  bool starting;
};


QScriptValue mapConstructor(QScriptContext * context, QScriptEngine * engine);

#endif
