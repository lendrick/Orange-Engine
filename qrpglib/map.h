#ifndef MAP_H
#define MAP_H 1

#include "polygon.h"
#include "bitmap.h"
#include <QtCore>

class Resource;
class Bitmap;
class Entity;

struct MapScript {
  MapScript(int c, QString s);
  int condition;
  QString script;
};

class Map : public QObject {
  Q_OBJECT
public:
  Map();
  Map(Bitmap * t, int x, int y, int w, int h, QString mapname = "Unnamed Map");
  ~Map();
  void Draw(int layer, int x, int y, float opacity);
  void GetTileSize(int &w, int &h);
  void GetSize(int layer, int &w, int &h);
  void SetTileset(Bitmap * t);
  void SetTileset(int layer, Bitmap * t);
  Bitmap * GetTileset();
  void Save(QString filename);
  Resource * ThisMap() { return thisMap; }
  Entity * GetEntity(int layer, int index);
  Entity * GetStartEntity(int layer, int index);
  void Update();
  QScriptValue scriptObject;
  QScriptValue getScriptObject();

public slots:
  bool SetName(QString n);
  QString GetName();
  void SetTile(int layer, int x, int y, int tile);
  int GetTile(int layer, int x, int y);
  int GetLayers();
  QString GetLayerName(int layer);
  void SetLayerName(int layer, QString name);
  int AddLayer(int w, int h, bool wrap=false, int filltile=0, QString name = "New Layer");
  void moveLayer(int oldIndex, int newIndex);
  void InsertLayerBefore(int layer, int w, int h, bool wrap=false, int filltile=0, QString name = "New Layer");
  void InsertLayerAfter(int layer, int w, int h, bool wrap=false, int filltile=0, QString name = "New Layer");
  void DeleteLayer(int layer);
  void SetViewport(int x, int y, int w, int h);
  void AddEntity(int layer, Entity * entity);
  void AddStartEntity(int layer, Entity * entity);
  void RemoveEntity(int layer, Entity * entity);
  void RemoveStartEntity(int layer, Entity * entity);
  int GetEntities(int layer);
  int GetStartEntities(int layer);
  void Reset();
  void Clear();
  void setStarting(bool);

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
    QList < Entity * > entities;
    QList < Entity * > startEntities;
    Bitmap * tileset;
    int tile_w, tile_h;
  };

  QList < Layer * > layers;

  Bitmap * tileset;

  Resource * thisMap;
  QList < MapScript > scripts;

  bool starting;
};


QScriptValue mapConstructor(QScriptContext * context, QScriptEngine * engine);

#endif
