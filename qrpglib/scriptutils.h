#ifndef SCRIPTUTILS_H
#define SCRIPTUTILS_H 1

#include <QtCore>
#include <QtScript>
#include "map.h"
#include "player.h"

class Entity;

class ScriptUtils : public QObject, public QScriptable {
  Q_OBJECT

public:
  ScriptUtils();

public slots:
  void messageBox(QString s);
  void print(QString s);
  QScriptValue getEntity(QString s);
  QScriptValue teleport(QString, int, int);
  void setCamera(Entity * e);
};

#endif
