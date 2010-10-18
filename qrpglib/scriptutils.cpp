#include <QtCore>
#include <QtScript>
#include <QtDeclarative>
#include "scriptutils.h"
#include "globals.h"
#include "map.h"
#include "entity.h"
#include "npc.h"
#include "player.h"
#include "mapscene.h"
#include "mapbox.h"
#include "sound.h"

static QScriptValue f(QScriptContext* c, QScriptEngine* e)
{
  qDebug() << "CALL: " << c->callee().toString();
  cprint("Call to " + c->callee().toString());
  return QScriptValue();
}


ScriptUtils::ScriptUtils() : QObject() {
  QScriptValue objectValue = scriptEngine->newQObject(this);
  scriptEngine->globalObject().setProperty("rpgx", objectValue);

  QScriptValue npcCtor = scriptEngine->newFunction(npcConstructor);
  QScriptValue metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, npcCtor);
  scriptEngine->globalObject().setProperty("Npc", metaObject);

  QScriptValue soundCtor = scriptEngine->newFunction(soundConstructor);
  metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, soundCtor);
  scriptEngine->globalObject().setProperty("Sound", metaObject);

  /*
  QScriptValue alertFunc = scriptEngine->newFunction(alert);
  metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, alertFunc);
  scriptEngine->globalObject().setProperty("alert", metaObject);
  */

  const QMetaObject* obj = this->metaObject();
  for(int i = obj->methodOffset(); i < obj->methodCount(); ++i) {
    QString name = QString::fromLatin1(obj->method(i).signature());

    if(obj->method(i).methodType() == QMetaMethod::Slot &&
       obj->method(i).access() == QMetaMethod::Public) {
      qDebug() << "slot: " << name;
      QScriptValue func = scriptEngine->newFunction(f); //obj->method(i).signature());
      metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, func);
      scriptEngine->globalObject().setProperty(QString::fromLatin1(obj->method(i).signature()),
                                               metaObject);

      //scriptEngine->globalObject().setProperty(name, objectValue.property(name));
    }
  }



  QScriptValueIterator i(objectValue);

  while(i.hasNext()) {
    i.next();
    qDebug() << "Object: " << i.name();
    //scriptEngine->globalObject().setProperty(i.name(), i.value());
  }


  qScriptRegisterMetaType(scriptEngine, entityPointerToScriptValue, entityPointerFromScriptValue);
}

void ScriptUtils::alert(QString s) {
  message(s);
}

void ScriptUtils::print(QString s) {
  cprint(s);
}

QScriptValue ScriptUtils::getEntity(QString s) {
  EntityPointer e = entities[mapentitynames[s]];
  return e->getScriptObject();
}

QScriptValue ScriptUtils::teleport(QString map, int x, int y) {
  return QScriptValue(QScriptValue::NullValue);
}

void ScriptUtils::setCamera(EntityPointer e) {
  cprint("Setting camera");
  mapBox->setCamera(e);
}

void ScriptUtils::setMap(QString m) {
  cprint("Setting map to " + m);
  mapBox->setMap(mapnames[m]);
}

void ScriptUtils::setLayer(int l) {
  cprint("Setting layer to " + QString::number(l));
  mapBox->setLayer(l);
}

void ScriptUtils::addQml(QString filename) {
  QDeclarativeComponent component(declarativeEngine, filename);
  QGraphicsObject * c = qobject_cast<QGraphicsObject *>(component.create());
  mapBox->mapScene->addItem(c);
}

void ScriptUtils::addQmlString(QString string) {
  QDeclarativeComponent component(declarativeEngine);
  component.setData(string.toAscii(), QUrl());
  QGraphicsObject * c = qobject_cast<QGraphicsObject *>(component.create());
  mapBox->mapScene->addItem(c);
}

QScriptValue ScriptUtils::include(QString filename) {
  cprint("evaluating file '" + filename + "'");
  QFile f(filename);
  f.open(QIODevice::ReadOnly);

  if(!f.exists()) {
    message("File '" + filename +"' not found");
    return QScriptValue();
  }

  QTextStream in(&f);
  QString program(in.readAll());
  f.close();
  //qDebug() << program;
  QScriptValue r = scriptEngine->evaluate(program, filename);
  if(scriptEngine->hasUncaughtException()) {
    cprint(filename + ": " + QString::number(scriptEngine->uncaughtExceptionLineNumber()) + ": " +
            scriptEngine->uncaughtException().toString());
    scriptEngine->clearExceptions();
  }

  return r;
}
