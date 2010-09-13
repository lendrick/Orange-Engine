#ifndef PROJECT_H
#define PROJECT_H 1

#include <QtCore>

class Project : public QObject {
  Q_OBJECT
public:
  Project(QString projname = "");
  ~Project();
  void SetName(QString projname);
  void Load(QString filename);
  void Save(QString filename);
private:
  QString name;
signals:
  void UpdateName(QString);
};

class ProjectReader : public QXmlStreamReader {
public:
  Project * read(QIODevice * device);
  Project * read(QString filename);

private:
  void readProject();
  void readMaps();
  void readSprites();
  void readTilesets();
  void readUnknownElement();

  Project * project;
  QList < QString > maplist;
  QList < QString > spritelist;
  QList < QString > tilesetlist;
  QFileInfo fileinfo;
};

#endif
