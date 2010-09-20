#include <QtCore>
#include "project.h"
#include "globals.h"
#include "map.h"
#include "bitmap.h"
#include "sprite.h"
#include "mapreader.h"
#include "rpgengine.h"

Project::Project(QString projname) {
  name = projname;
  //connect(this, SIGNAL(UpdateName(QString)), mainWindow, SLOT(UpdateProjectTitle(QString)));
  emit UpdateName(name);
}

Project::~Project() {
  currentresource = 0;
  RPGEngine::setCurrentMap(0);
  mapfolder->clear();
  spritefolder->clear();
  bitmapfolder->clear();

  while (!maps.isEmpty())
    delete maps.takeFirst();
  while (!bitmaps.isEmpty())
    delete bitmaps.takeFirst();
  while (!sprites.isEmpty())
    delete sprites.takeFirst();
}

void Project::SetName(QString projname) {
  name = projname;
  emit UpdateName(name);
}

void Project::Save(QString filename) {
  // Create project directory
  QDir dir(QDir::current());
  dir.mkdir(filename);
  dir.cd(filename);
  QDir::setCurrent(filename);

  // Create subdirectories
  dir.mkdir("tilesets");
  dir.mkdir("maps");
  dir.mkdir("sprites");

  // Create project file
  //message(QDir::currentPath());
  filename = dir.dirName() + ".xproj";
  QFile outfile(filename);
  outfile.open(QIODevice::WriteOnly);
  QTextStream f(&outfile);
  
  f << "<!DOCTYPE xproj>\n";
  f << "<project>\n";

  f << "  <name>" << name << "</name>\n";

  // Output tilesets
  f << "  <tilesets>\n";
  QDir::setCurrent("tilesets");
  for(int i = 0; i < bitmaps.size(); i++) {
    if(bitmaps[i]) {
      QString fn = bitmaps[i]->GetName();
      fn = fn + ".xtile";
      bitmaps[i]->Save(fn);

      f << "    <tileset>";
      f << fn;
      f << "</tileset>\n";
    }
  }
  QDir::setCurrent("..");
  f << "  </tilesets>\n";

  // Output maps
  f << "  <maps>\n";
  QDir::setCurrent("maps");
  for(int i = 0; i < maps.size(); i++) {
    if(maps[i]) {
      QString fn = maps[i]->getName();
      fn = fn + ".xmap";
      maps[i]->save(fn);

      f << "    <map>";
      f << fn;
      f << "</map>\n";
    }
  }
  QDir::setCurrent("..");
  f << "  </maps>\n";

  f << "  <sprites>\n";
  QDir::setCurrent("sprites");
  for(int i = 0; i < sprites.size(); i++) {
    if(sprites[i]) {
      QString fn = sprites[i]->GetName();
      fn = fn + ".xspr";
      sprites[i]->Save(fn);

      f << "    <sprite>";
      f << fn;
      f << "</sprite>\n";
    }
  }

  QDir::setCurrent("..");
  f << "  </sprites>\n";

  f << "</project>\n";
  outfile.close();

  // Leave project directory
  QDir::setCurrent("..");
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

