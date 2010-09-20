#ifndef PROJECTREADER_H
#define PROJECTREADER_H

#include <QtCore>

class Project;

class ProjectReader : public QXmlStreamReader {
public:
  Project * read(QIODevice * device);
  Project * read(QString filename);

private:
  void readProject();
  void readMaps();
  void readSprites();
  void readTilesets();
  void readScripts();
  void readUnknownElement();
  void tokenDebug();

  Project * project;
  QList < QString > maplist;
  QList < QString > spritelist;
  QList < QString > tilesetlist;
  QFileInfo fileinfo;
};


#endif // PROJECTREADER_H
