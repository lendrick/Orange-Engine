#include <QtCore>
#include "resource.h"

Resource::Resource(ResType t, int i, QString name, QTreeWidget * parent) :
  QTreeWidgetItem(parent) {
  id = i;
  restype = t;
  setText(0, name);
  setExpanded(true);
}

Resource::Resource(ResType t, int i, QString name, QTreeWidgetItem * parent) :
  QTreeWidgetItem(parent) {
  id = i;
  restype = t;
  setText(0, name);
}

int Resource::getID() {
  return id;
}

Resource::ResType Resource::type() {
  return restype;
}

void Resource::clear() {
  while( QTreeWidgetItem * c = child(0)) {
    delete c;
  }
}