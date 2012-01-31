#include "mapreadertiled.h"
#include "map.h"
#include "newmapdialog.h"
#include "globals.h"
#include <QtCore>

void MapReaderTiled::tokenDebug()
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

Map * MapReaderTiled::read(QIODevice * device)
{
  setDevice(device);
  map = 0;

  NewMapDialog newmapdialog((QWidget *)mainWindow);

  while (!atEnd()) {
    readNext();
    qDebug() << ("read: Token (" + tokenString() + "): " + name().toString());
    if (isStartElement()) {
      if (name() == "map")
        readMap();
      else
        raiseError(QObject::tr("This is not a tmx file."));
    }
  }

  if(!error()) {
    if(newmapdialog.exec() == QDialog::Accepted ) {
      //tiles->tilebox->makeCurrent();
      map->setName(newmapdialog.mapname->text());
      map->setTileset(bitmaps[newmapdialog.tileset->currentIndex()]);
      maplist->setCurrentItem(map->getThisMap());
      return map;
    }
  }

  return 0;
}

Map * MapReaderTiled::read(QString filename)
{
  QFile f(filename);
  f.open(QIODevice::ReadOnly);
  return read(&f);
}

void MapReaderTiled::readMap()
{
  Q_ASSERT(isStartElement() && name() == "map");
  map = new Map();

  while (!atEnd()) {
    readNext();
    qDebug() << ("readMap: Token (" + tokenString() + "): " + name().toString());

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "layer")
      {
        readLayer();
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void MapReaderTiled::readLayer()
{
  Q_ASSERT(isStartElement() && name() == "layer");

  QString layerName;
  int h = 0;
  int w = 0;
  QList<int> layerData;
  int currentLayer = 0;
  QList< EntityPointer > entities;

  w = attributes().value("width").toString().toInt();
  h = attributes().value("height").toString().toInt();
  layerName = attributes().value("name").toString();

  while (!atEnd()) {
    readNext();
    qDebug() << ("readLayer: Token (" + tokenString() + "): " + name().toString() + " " + layerName);
    tokenDebug();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "data")
      {
        readLayerData(layerData);
      }
      else
      {
        readUnknownElement();
      }
    }
  }

  if(layerName.isEmpty() || layerName.isNull())
    currentLayer = map->addLayer(w, h, false, 0, "Layer " + QString::number(map->getLayerCount() + 1));
  else
    currentLayer = map->addLayer(w, h, false, 0, layerName);

  for(int y = 0; y < h; y++)
  {
    for(int x = 0; x < w; x++)
    {
      int tile = layerData.takeFirst();
      map->setTile(currentLayer, x, y, tile);
    }
  }

  while(!(entities.isEmpty()))
    map->addStartEntity(currentLayer, entities.takeFirst());
}

void MapReaderTiled::readLayerData(QList<int> & layerData)
{
  Q_ASSERT(isStartElement() && name() == "data");

  while (!atEnd()) {
    readNext();
    //qDebug() << ("readLayerData: Token (" + tokenString() + "): " + name().toString());
    tokenDebug();

    if (isEndElement() && name() == "data")
      break;

    if (isStartElement()) {
      if (name() == "tile")
      {
        int tile = 0;
        tile = attributes().value("gid").toString().toInt();
        layerData.push_back(tile);
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void MapReaderTiled::readUnknownElement()
{
  Q_ASSERT(isStartElement());

  while (!atEnd()) {
    readNext();
    qDebug() << ("readUnknownElement: Token (" + tokenString() + "): " + name().toString());

    if (isEndElement())
      break;

    if (isStartElement())
      readUnknownElement();
  }
}
