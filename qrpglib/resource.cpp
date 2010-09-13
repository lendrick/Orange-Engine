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

int Resource::GetID() {
  return id;
}

Resource::ResType Resource::Type() {
  return restype;
}

void Resource::clear() {
  while( QTreeWidgetItem * c = child(0)) {
    delete c;
  }
}