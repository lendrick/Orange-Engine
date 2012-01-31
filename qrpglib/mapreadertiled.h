#ifndef MAPREADERTILED_H
#define MAPREADERTILED_H

#include <QtCore>

class Map;
class Entity;

typedef QSharedPointer<Entity> EntityPointer;

class MapReaderTiled : public QXmlStreamReader
{
public:
  Map * read(QIODevice * device);
  Map * read(QString filename);

private:
  void readMap();
  void readLayer();
  void readLayerData(QList<int> & layerData);

  void readUnknownElement();
  void tokenDebug();

  Map * map;
};
#endif // MAPREADERTILED_H
