#ifndef MAPREADER_H
#define MAPREADER_H

#include <QtCore>

class Map;
class Entity;

typedef QSharedPointer<Entity> EntityPointer;

class MapReader : public QXmlStreamReader
{
public:
  Map * read(QIODevice * device);
  Map * read(QString filename);

private:
  void readMap();
  void readLayer();
  void readLayerData(QList<int> & layerData);
  void readEntities(QList < EntityPointer > & entities);
  EntityPointer readEntity();
  void readEntityScripts(EntityPointer e);
  void readScripts();

  void readUnknownElement();
  void tokenDebug();

  Map * map;
};

#endif // MAPREADER_H
