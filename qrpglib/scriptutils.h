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
  void init();

public slots:
  void alert(QString s);
  void print(QString s);
  void debug(QString s);
  void pause();
  void unPause();
  QScriptValue getEntity(QString s);
  QScriptValue teleport(QString, int, int);
  QScriptValue createComponent(QString filename);
  QScriptValue createComponent(QString filename, QObject * parent);
  QScriptValue copy(QScriptValue v);
  void setCamera(EntityPointer e);
  void setMap(QString m);
  void setLayer(int l);
  void addQml(QString filename);
  void addQmlString(QString string);
  QScriptValue include(QString filename);
  void dumpScriptObject(QScriptValue objectValue);
  bool same(QObject * a, QObject * b);

signals:
  void menuKey();
};

Q_DECLARE_METATYPE(QScriptValue);


#endif
