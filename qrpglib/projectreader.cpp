#include "projectreader.h"
#include "mapreader.h"
#include "bitmap.h"
#include "sprite.h"
#include "project.h"
#include "rpgengine.h"
#include "globals.h"

void ProjectReader::tokenDebug()
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

Project * ProjectReader::read(QIODevice * device)
{

  setDevice(device);
  project = 0;

  //message("reading project");

  while (!atEnd()) {
    readNext();
    //message("read: Token (" + tokenString() + "): " + name().toString());
    if (isStartElement()) {
      if (name() == "project")
        readProject();
      else
        raiseError(QObject::tr("This is not an xpro file."));
    }
  }

  if(!error())
    return project;
  else
    return 0;
}

Project * ProjectReader::read(QString filename)
{
  //qDebug() << "reading project " << filename;
  QFile f(filename);
  f.open(QIODevice::ReadOnly);
  fileinfo = QFileInfo(f);
  return read(&f);
}

void ProjectReader::readProject()
{
  Q_ASSERT(isStartElement() && name() == "project");
  project = new Project();
  bool dirExists;

  //message("readProject");

  QDir::setCurrent(fileinfo.absolutePath());

  // Since we need to load our bitmaps first, we just read in all of the filenames
  // and then load the actual resources last.  That way, if <tilesets> isn't the
  // first section, there won't be any errors.

  while (!atEnd()) {
    readNext();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "name")
      {
        project->SetName(readElementText());
        //message("Map name: " + map->GetName());
      }
      else if (name() == "maps")
      {
        readMaps();
      }
      else if (name() == "tilesets")
      {
        readTilesets();
      }
      else if (name() == "sprites")
      {
        readSprites();
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

  // Load bitmaps
  dirExists = QDir::setCurrent("tilesets");
  BitmapReader bitmapReader;
  while(!tilesetlist.isEmpty()) {
    QString b = tilesetlist.takeFirst();
    // load bitmap
    bitmapReader.read(b);
  }
  if(dirExists) QDir::setCurrent("..");

  // load sprites
  dirExists = QDir::setCurrent("sprites");
  SpriteReader spriteReader;
  while(!spritelist.isEmpty()) {
    QString s = spritelist.takeFirst();
    // load sprite
    spriteReader.read(s);
  }
  if(dirExists) QDir::setCurrent("..");

  // load maps
  dirExists = QDir::setCurrent("maps");
  MapReader mapReader;
  while(!maplist.isEmpty()) {
    QString m = maplist.takeFirst();
    // load map
    mapReader.read(m);
  }
  if(dirExists) QDir::setCurrent("..");

}

void ProjectReader::readMaps()
{
  Q_ASSERT(isStartElement() && name() == "maps");
  //message("readMaps");

  while (!atEnd()) {
    readNext();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "map")
      {
        maplist.push_back(QString(readElementText()));
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void ProjectReader::readSprites()
{
  Q_ASSERT(isStartElement() && name() == "sprites");

  while (!atEnd()) {
    readNext();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "sprite")
      {
        spritelist.push_back(QString(readElementText()));
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void ProjectReader::readTilesets()
{
  Q_ASSERT(isStartElement() && name() == "tilesets");


  while (!atEnd()) {
    readNext();

    if (isEndElement())
      break;

    if (isStartElement()) {
      if (name() == "tileset")
      {
        tilesetlist.push_back(QString(readElementText()));
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void ProjectReader::readScripts()
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

        RPGEngine::addScript(condition, script);
      }
      else
      {
        readUnknownElement();
      }
    }
  }
}

void ProjectReader::readUnknownElement()
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

