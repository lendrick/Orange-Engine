#include "mapreader.h"
#include "map.h"
#include "npc.h"
#include "player.h"
#include "entity.h"

void MapReader::tokenDebug()
{
  if(isCharacters ())
  {
   // message("DEBUG -- CHARACTERS: " + readElementText());
  }
  else
  {
    //message("DEBUG: " + tokenString() + ": " + name().toString() + " [" + readElementText() + "]");
  }
}

Map * MapReader::read(QIODevice * device)
{
  setDevice(device);
  map = 0;

  while (!atEnd()) {
    readNext();
    //message("read: Token (" + tokenString() + "): " + name().toString());
    if (isStartElement()) {
      if (name() == "map")
        readMap();
      else
        raiseError(QObject::tr("This is not an xmap file."));
    }
  }

  if(!error())
    return map;
  else
    return 0;
}

Map * MapReader::read(QString filename)
{
  QFile f(filename);
  f.open(QIODevice::ReadOnly);
  return read(&f);
}

void MapReader::readMap()
{
  Q_ASSERT(isStartElement() && name() == "map");
  map = new Map();

  while (!atEnd()) {
    readNext();
    //message("readMap: Token (" + tokenString() + "): " + name().toString());

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "name")
      {
        map->SetName(readElementText());
        //message("Map name: " + map->GetName());
      }
      else if (name() == "layer")
      {
        readLayer();
      }
      else if (name() == "tileset")
      {
        map->SetTileset(bitmaps[bitmapnames[readElementText()]]);
      }
      else if (name() == "scripts")
      {
        readScripts();
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void MapReader::readLayer()
{
  Q_ASSERT(isStartElement() && name() == "layer");

  QString tileset;
  QString layerName;
  int h = 0;
  int w = 0;
  QList<int> layerData;
  int currentLayer = 0;
  QList< Entity * > entities;

  while (!atEnd()) {
    readNext();
    //message("readLayer: Token (" + tokenString() + "): " + name().toString());
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "width")
      {
        w = readElementText().toInt();
        //message("WIDTH: " + w);
      }
      else if (name() == "height")
      {
        h = readElementText().toInt();
        //message("HEIGHT: " + h);
      }
      else if (name() == "tileset")
      {
        tileset = readElementText();
      }
      else if (name() == "name")
      {
        layerName = readElementText();
      }
      else if (name() == "layerdata")
      {
        readLayerData(layerData);
      }
      else if (name() == "entities")
      {
        readEntities(entities);
      }
      else
      {
        readUnknownElement();
      }
    }
  }

  if(layerName.isEmpty() || layerName.isNull())
    currentLayer = map->AddLayer(w, h, false, 0, "Layer " + QString::number(map->GetLayers() + 1));
  else
    currentLayer = map->AddLayer(w, h, false, 0, layerName);

  for(int y = 0; y < h; y++)
  {
    for(int x = 0; x < w; x++)
    {
      int tile = layerData.takeFirst();
      map->SetTile(currentLayer, x, y, tile);
    }
  }

  while(!(entities.isEmpty()))
    map->AddStartEntity(currentLayer, entities.takeFirst());
}

void MapReader::readLayerData(QList<int> & layerData)
{
  Q_ASSERT(isStartElement() && name() == "layerdata");

  QString dataString = readElementText();
  QTextStream data(&dataString);

  while(!data.atEnd())
  {
    int t = 0;
    data.skipWhiteSpace();
    data >> t;
    data.skipWhiteSpace();
    layerData.push_back(t);
  }
}

void MapReader::readEntities(QList < Entity * > & entities) {
  while (!atEnd()) {
    readNext();
    //message("readLayer: Token (" + tokenString() + "): " + name().toString());
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "entity")
      {
        Entity * e = readEntity();

        entities.append(e);
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

Entity * MapReader::readEntity() {
  QString ename = attributes().value("name").toString();
  QString sprite = attributes().value("sprite").toString();
  int x = attributes().value("x").toString().toInt();
  int y = attributes().value("y").toString().toInt();
  int state = attributes().value("state").toString().toInt();

  Entity * e = new Npc(ename);

  e->setSprite(sprite);
  e->setPos(x, y);
  e->setState(state);

  while (!atEnd()) {
    readNext();
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "scripts")
      {
        readEntityScripts(e);
      }
      else
      {
        readUnknownElement();
      }
    }
  }

  return e;
}

void MapReader::readEntityScripts(Entity * e) {
  while (!atEnd()) {
    readNext();
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "script")
      {
        int condition = attributes().value("condition").toString().toInt();
        bool defCoords = !(attributes().hasAttribute("x1"));
        int x1, y1, x2, y2;
        x1 = y1 = x2 = y2 = 0;
        if(!defCoords) {
          x1 = attributes().value("x1").toString().toInt();
          y1 = attributes().value("y1").toString().toInt();
          x2 = attributes().value("x2").toString().toInt();
          y2 = attributes().value("y2").toString().toInt();
        }
        QString script = readElementText();

        e->addScript(condition, script, defCoords, x1, y1, x2, y2);
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void MapReader::readScripts()
{
  while (!atEnd()) {
    readNext();
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "script")
      {
        int condition = attributes().value("condition").toString().toInt();
        QString script = readElementText();

        map->addScript(condition, script);
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void MapReader::readUnknownElement()
{
  Q_ASSERT(isStartElement());

  while (!atEnd()) {
    readNext();
    //message("readUnknownElement: Token (" + tokenString() + "): " + name().toString());

    if (isEndElement())
      break;

    if (isStartElement())
      readUnknownElement();
  }
}
