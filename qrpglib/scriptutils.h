#ifndef SCRIPTUTILS_H
#define SCRIPTUTILS_H 1

#include <QtCore>
#include <QtScript>
#include <QtDeclarative>
#include "map.h"
#include "player.h"

//Q_DECLARE_METATYPE(QDeclarativeListProperty<QGraphicsObject>);
//Q_SCRIPT_DECLARE_QMETAOBJECT(QDeclarativeListProperty<QDeclarativeItem>, QObject *);

class Entity;

class ScriptUtils : public QObject, public QScriptable {
  Q_OBJECT

public:
  ScriptUtils();
  void dumpObject(QObject * o);

public slots:
  void alert(QString s);
  void print(QString s);
  void debug(QString s);
  QScriptValue getEntity(QString s);
  QScriptValue teleport(QString, int, int);
  QScriptValue createComponent(QString filename);
  QScriptValue createComponent(QString filename, QObject * parent);
  void setCamera(EntityPointer e);
  void setMap(QString m);
  void setLayer(int l);
  void addQml(QString filename);
  void addQmlString(QString string);
  QScriptValue include(QString filename);
  void dumpScriptObject(QScriptValue objectValue);
};


#endif
