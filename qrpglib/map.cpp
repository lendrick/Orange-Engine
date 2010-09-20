#ifdef WIN32
#include <windows.h>
#endif

#include "map.h"
#include "globals.h"
#include "entity.h"
#include "npc.h"
#include <GL/gl.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <QXmlStreamReader>
#include <QtGui>
#include <QGLWidget>

using std::cout;
using std::ifstream;
using std::ofstream;

Map::Map(Bitmap * t, int x, int y, int w, int h, QString mapname) : QObject() {
  tileset = t;
  view_x = x;
  view_y = y;
  view_w = w;
  view_h = h;
  starting = true;
  if(tileset) tileset->GetSize(tile_w, tile_h);
  name = mapname;

  maps.push_back(this);
  mapnames[name] = maps.size() - 1;
  thisMap = 
    new Resource(Resource::Map,
	   maps.size() - 1, 
	   name,
	   mapfolder);

  scriptObject = scriptEngine->newQObject(this);
}

Map::Map()
{
  tileset = 0;
  view_x = view_y = view_w = view_h = 0;
  name = "Unnamed Map";
  starting = true;

  maps.push_back(this);
  mapnames[name] = maps.size() - 1;
  thisMap = 
    new Resource(Resource::Map,
	   maps.size() - 1, 
	   name,
	   mapfolder);

  scriptObject = scriptEngine->newQObject(this);
}

bool Map::setName(QString n)
{
  if(mapnames.contains(n)) {
    return false;
  }
  
  mapnames[n] = mapnames[name];
  mapnames.remove(name);
  name = n;
  thisMap->setText(0, name);
  return true;
}

QString Map::getName()
{
  return name;
}

QString Map::getLayerName(int layer) {
  return layers[layer]->name;
}

void Map::setLayerName(int layer, QString name) {
  layers[layer]->name = name;
}

Map::Tile::~Tile() {
  int i;
  for(i = 0; i < border.size(); i++) delete border[i];
}

Map::Layer::~Layer() {
  int i;
  for(i = 0; i < border.size(); i++) delete border[i];
  if(layerdata) delete layerdata; //free(layerdata);
}

Map::Layer::Layer() {
  layerdata = 0;
  tileset = 0;
}
  

Map::~Map() {
  int i;
  
  for(i = 0; i < tiles.size(); i++) delete tiles[i];
  for(i = 0; i < layers.size(); i++) delete layers[i];
}
    
void Map::update() {
  // Execute scripts.
  for(int i = 0; i < scripts.size(); i++) {
    bool execute = false;
    MapScript * s = &(scripts[i]);
    if(starting && s->condition == ScriptCondition::Start) {
      execute = true;
    } else if(s->condition == ScriptCondition::EveryFrame) {
      execute = true;
    }

    //push context
    if(execute) {
      //cprint("execute: " + s->script + "\n");
      QScriptContext * context = scriptEngine->pushContext();
      context->setThisObject(scriptObject);
      scriptEngine->evaluate(s->script);

      if(scriptEngine->hasUncaughtException())
        message(scriptEngine->uncaughtException().toString());

      scriptEngine->popContext();
    }
  }

  // update entities
  for(int i = 0; i < layers.size(); i++) {
    for(int j = 0; j < layers[i]->entities.size(); j++) {
      layers[i]->entities[j]->update();
    }
  }

  starting = false;
}

void Map::getTileSize(int &w, int &h) {
  w = tile_w;
  h = tile_h;
}

void Map::getSize(int layer, int &w, int &h) {
  if(layer < layers.size()) {
    w = layers[layer]->width;
    h = layers[layer]->height;
  } else {
    w = 0; 
    h = 0;
  }
}

Bitmap * Map::getTileset() {
  return tileset;
}

void Map::setViewport(int x, int y, int w, int h) {
  view_x = x;
  view_y = y;
  view_w = w;
  view_h = h;
}

void Map::draw(int layer, int x, int y, float opacity) {
  if(tileset) {
    int xs, ys, h, w, x_off, y_off;
    int i, j;
    
    xs = x / tile_w;
    ys = y / tile_h;
    w = view_w / tile_w + 2;
    h = view_h / tile_h + 2;
    x_off = x % tile_w;
    y_off = y % tile_h; 
    if(x_off == tile_w) x_off = 0;
    if(y_off == tile_h) y_off = 0;
    
    for(j = ys; j < ys + h; j++) {
      for(i = xs; i < xs + w; i++) {
        if(i >= 0 && i < layers[layer]->width && j >= 0 && j < layers[layer]->height) {
          int tile_x = (i - xs) * tile_w - x_off + view_x;
          int tile_y = (j - ys) * tile_h - y_off + view_y;
          
          tileset->Draw(getTile(layer, i, j), tile_x, tile_y, opacity);
        }
      }
    }

    // Sort in Y direction
    if(play) {
      if(layers[layer]->entities.size()) 
        qSort(layers[layer]->entities.begin(), layers[layer]->entities.end(), entity_y_order);
      
      for(i = 0; i < layers[layer]->entities.size(); i++) {
        layers[layer]->entities[i]->draw(x, y);
      }
    } else {
      if(layers[layer]->startEntities.size()) 
        qSort(layers[layer]->startEntities.begin(), layers[layer]->startEntities.end(), entity_y_order);
      
      for(i = 0; i < layers[layer]->startEntities.size(); i++) {
        layers[layer]->startEntities[i]->draw(x, y, opacity);
      }
    }

  }
}

void Map::addEntity(int layer, Entity * entity) {
  removeEntity(entity->getLayer(), entity);
  if(layer < layers.size()) {
    if(play)
      layers[layer]->entities.push_back(entity);
    else
      layers[layer]->startEntities.push_back(entity);      

    entity->setLayer(layer);
  }
}

void Map::addStartEntity(int layer, Entity * entity) {
  layers[layer]->startEntities.push_back(entity);      
}

void Map::removeEntity(int layer, Entity * entity) {
  if(layer < layers.size()) {
    if(play)
      layers[layer]->entities.removeAll(entity);
    else
      layers[layer]->startEntities.removeAll(entity);      
  }
}

void Map::removeStartEntity(int layer, Entity * entity) {
  layers[layer]->startEntities.removeAll(entity);  
}

int Map::getEntities(int layer) {
  if(layer < layers.size())
    return layers[layer]->entities.size();
  return 0;
}

int Map::getStartEntities(int layer) {
  if(layer < layers.size())
    return layers[layer]->startEntities.size();
  return 0;
}

Entity * Map::getEntity(int layer, int index) {
  if(layer < layers.size() && index < layers[layer]->entities.size())
    return layers[layer]->entities[index];
  return 0;
}

Entity * Map::getStartEntity(int layer, int index) {
  if(layer < layers.size() && index < layers[layer]->startEntities.size())
    return layers[layer]->startEntities[index];
  return 0;
}


int Map::getTile(int layer, int x, int y) {
  if(layer < layers.size() &&
     x >= 0 && x < layers[layer]->width &&
     y >= 0 && y < layers[layer]->height) 
    return layers[layer]->layerdata[x + y * layers[layer]->width];
  return 0;
}

void Map::setTile(int layer,
		  int x, int y, int tile) {
  if(layer < layers.size() &&
     x >= 0 && x < layers[layer]->width &&
     y >= 0 && y < layers[layer]->height) 
    layers[layer]->layerdata[x + y * layers[layer]->width] = tile;
}

int Map::getLayers() {
  return layers.size();
}

void Map::setTileset(Bitmap * t) {
  tileset = t;
  tileset->GetSize(tile_w, tile_h);
}

void Map::setTileset(int layer, Bitmap * t) {
  layers[layer]->tileset = t;
  t->GetSize(layers[layer]->tile_w, layers[layer]->tile_h);
}

int Map::addLayer(int w, int h, bool wrap, int filltile, QString name) {
  int i;

  Layer * l = new Layer;
  l->height = h;
  l->width = w;
  l->wrap = wrap;
  l->name = name;
  l->layerdata = new int[h*w]; //(int *) malloc(h * w * sizeof(int));
  for(i = 0; i < h * w; i++) {
    l->layerdata[i] = filltile;
  }
  
  layers.push_back(l);
  return (int) layers.size() - 1;
}
  
void Map::moveLayer(int oldIndex, int newIndex) {
  layers.move(oldIndex, newIndex);
}

void Map::insertLayerBefore(int layer, int w, int h, bool wrap, int filltile, QString name) {
  int l = addLayer(w, h, wrap, filltile, name);
  moveLayer(l, layer);
}

void Map::insertLayerAfter(int layer, int w, int h, bool wrap, int filltile, QString name) {
  int l = addLayer(w, h, wrap, filltile, name);
  moveLayer(l, layer + 1);
}

void Map::deleteLayer(int layer) {
  Layer * l = layers.takeAt(layer);
  delete l;
}

void Map::save(QString filename) {
  ofstream file(filename.toAscii());
  int i, x, y;
  int s = layers.size();

  file << "<map>\n";
  file << "  <name>" << name.toAscii().data() << "</name>\n";
  file << "  <layers>" << s << "</layers>\n";
  file << "  <tileset>" << getTileset()->GetName().toAscii().data() << "</tileset>\n";

  file << "  <scripts>";
  for(int y = 0; y < getScriptCount(); y++) {
    int cond = getScriptCondition(y);
    file << "    <script condition='" << cond << "'";
    file << "><![CDATA[";
    QString s = getScript(y);
    escapeCData(s);
    file << s.toAscii().data();
    file << "]]></script>\n";
  }
  file << "  </scripts>";

  for(i = 0; i < layers.size(); i++) {
    file << "  <layer>\n";
    file << "    <width>" << layers[i]->width << "</width>\n";
    file << "    <height>" << layers[i]->height << "</height>\n";
    file << "    <tileset>" << getTileset()->GetName().toAscii().data() << "</tileset>\n";
    file << "    <name>" << layers[i]->name.toAscii().data() << "</name>\n";
    file << "    <layerdata>\n";
    for(y = 0; y < layers[i]->width; y++) {
      file << "      ";
      for(x = 0; x < layers[i]->height; x++) {
        file << layers[i]->layerdata[y*layers[i]->width+x] << " ";
      }
      file << "\n";
    }
    file << "    </layerdata>\n";
    file << "    <entities>\n";
    for(x = 0; x < getStartEntities(i); x++) {
      Entity * e = getStartEntity(i, x);
      QString name = e->getName();
      int state = e->getState();
      int x = e->getX();
      int y = e->getY();
      QString sprite = e->getSprite()->GetName();
      file << "      <entity name='" << name.toAscii().data() << "' state='" <<
        state << "' x='" << x << "' y='" << y <<
        "' sprite='" << sprite.toAscii().data() << "'>\n";
      file << "        <scripts>\n";
      for(int y = 0; y < e->getScriptCount(); y++) {
        int cond = e->getScriptCondition(y);
        int x1, y1, x2, y2;
        x1 = y1 = x2 = y2 = 0;
        bool defCoords = e->usesDefaultBounds(y);
        if(!defCoords) {
          e->getScriptBoundingBox(y, x1, y1, x2, y2);
        }

        file << "          <script condition='" << cond << "'";
        if(!defCoords) {
          file << " x1='" << x1 << "' y1='" << y1 << "'";
          file << " x2='" << x2 << "' y2='" << y2 << "'";
        }
        file << "><![CDATA[";
        QString s = e->getScript(y);
        escapeCData(s);
        file << s.toAscii().data();
        file << "]]></script>\n";
      }
      file << "        </scripts>\n";
      file << "      </entity>\n";
    }
    file << "    </entities>\n";
    file << "  </layer>\n";
  }
  file << "</map>\n";
  file.close();
}

void Map::reset() {
  clear();

  for(int i = 0; i < layers.size(); i++) {
    for(int j = 0; j < layers[i]->startEntities.size(); j++) {
      Entity * e = layers[i]->startEntities[j];
      //Entity * newEntity = e->clone();

      //layers[i]->entities.append(newEntity);
      e->addToMap(i);
      mapentitynames[e->getName()] = e->getId();
    }
  }
}

void Map::clear() {
  for(int i = 0; i < layers.size(); i++) {
    while(!(layers[i]->entities.isEmpty()))
      delete layers[i]->entities.takeFirst();

    mapentitynames.clear();
  }
}

void Map::setStarting(bool s) {
  starting = s;
}

void Map::addScript(int cond, QString scr) {
  scripts.append(MapScript(cond, scr));
}

void Map::clearScripts() {
  scripts.clear();
}

int Map::getScriptCount() const {
  return scripts.size();
}

QString Map::getScript(int index) const {
  return scripts[index].script;
}

int Map::getScriptCondition(int index) const {
  return scripts[index].condition;
}

QScriptValue Map::getScriptObject() {
  return scriptObject;
}

MapScript::MapScript(int c, QString s) {
  condition = c;
  script = s;
};

QScriptValue mapConstructor(QScriptContext * context, QScriptEngine * engine) {
  QString name = context->argument(0).toString();
  Map * object = new Map();
  return engine->newQObject(object, QScriptEngine::QtOwnership);
}
