#ifndef RESOURCE_H
#define RESOURCE_H 1

#include <QtCore>
#include <QtGui>

class Resource : public QTreeWidgetItem {
public:
  enum ResType {
    Map,
    Sprite,
    Tileset,
    Bitmap,
    Folder,
    Script,
    Entity
  };

  Resource(ResType t, int i, QString name, QTreeWidgetItem * parent);
  Resource(ResType t, int i, QString name, QTreeWidget * parent);
  void clear();
  int getID();
  ResType type();
private:
  int id;
  ResType restype;
};

#endif
