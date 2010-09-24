#include <QtCore>
#include "project.h"
#include "globals.h"
#include "map.h"
#include "bitmap.h"
#include "sprite.h"
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
    maps.takeFirst()->deleteLater();
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

  f << "  <scripts>";
  for(int y = 0; y < RPGEngine::getScriptCount(); y++) {
    QString xml = globalScripts[y].toXml(4);
    f << xml.toAscii().data();
  }
  f << "  </scripts>\n";

  // Output tilesets
  f << "  <tilesets>\n";
  QDir::setCurrent("tilesets");
  for(int i = 0; i < bitmaps.size(); i++) {
    if(bitmaps[i]) {
      QString fn = bitmaps[i]->getName();
      fn = fn + ".xtile";
      bitmaps[i]->save(fn);

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
      QString fn = sprites[i]->getName();
      fn = fn + ".xspr";
      sprites[i]->save(fn);

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
