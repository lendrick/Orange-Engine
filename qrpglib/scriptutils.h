#ifndef SCRIPTUTILS_H
#define SCRIPTUTILS_H 1

#include <QtCore>
#include <QtScript>

class Entity;

class ScriptUtils : public QObject, public QScriptable {
  Q_OBJECT
public:
  ScriptUtils();
public slots:
  void messageBox(QString s);
  void print(QString s);
  QScriptValue getEntity(QString s);
  QScriptValue getMap();
  QScriptValue teleport(QString, int, int);
  QScriptValue player();
  void setCamera(Entity * e);
};

#endif
