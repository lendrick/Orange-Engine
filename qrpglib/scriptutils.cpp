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

QScriptValue bindObjectConstructor(QScriptContext * context, QScriptEngine * engine);

static QScriptValue f(QScriptContext* c, QScriptEngine* e)
{
  qDebug() << "CALL: " << c->callee().toString();
  cprint("Call to " + c->callee().toString());
  return QScriptValue();
}


ScriptUtils::ScriptUtils() : QObject() {

  /*
  QScriptValue alertFunc = scriptEngine->newFunction(alert);
  metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, alertFunc);
  scriptEngine->globalObject().setProperty("alert", metaObject);
  */

  /*
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
  */
  init();
}

void ScriptUtils::init() {
  QScriptValue global = copy(scriptEngine->globalObject());
  scriptEngine->setGlobalObject(global);
  QScriptValue objectValue = scriptEngine->newQObject(this);
  //dumpScriptObject(scriptEngine->globalObject());
  qDebug() << "scriptvalue rpgx " << global.isObject();
  scriptEngine->globalObject().setProperty("rpgx", objectValue);

  QScriptValue npcCtor = scriptEngine->newFunction(npcConstructor);
  QScriptValue metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, npcCtor);
  scriptEngine->globalObject().setProperty("Npc", metaObject);

  QScriptValue soundCtor = scriptEngine->newFunction(soundConstructor);
  metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, soundCtor);
  scriptEngine->globalObject().setProperty("Sound", metaObject);
  qScriptRegisterMetaType(scriptEngine, entityPointerToScriptValue, entityPointerFromScriptValue);

  scriptEngine->globalObject().setProperty("global", scriptEngine->globalObject());
  scriptEngine->globalObject().setProperty("mapBox", scriptEngine->newQObject(mapBox));
  scriptEngine->globalObject().setProperty("mapScene", scriptEngine->newQObject(mapBox->mapScene));

  qDebug() << "connecting signal";
  connect(mapBox->mapScene, SIGNAL(menuKey()), this, SIGNAL(menuKey()));
}

void ScriptUtils::alert(QString s) {
  message(s);
}

void ScriptUtils::print(QString s) {
  cprint(s);
}

void ScriptUtils::debug(QString s) {
  //qDebug() << "DEBUG";
  qDebug() << s;
}

void ScriptUtils::pause() {
  paused = true;
}

void ScriptUtils::unPause() {
  paused = false;
}

QScriptValue ScriptUtils::getEntity(QString s) {
  EntityPointer e = entities[mapentitynames[s]];
  return e->getScriptObject();
}

QScriptValue ScriptUtils::teleport(QString map, int x, int y) {
  return QScriptValue(QScriptValue::NullValue);
}

QScriptValue ScriptUtils::copy(QScriptValue v) {
  QScriptValue c = scriptEngine->newObject();
  QScriptValueIterator i(v);

  while(i.hasNext()) {
    i.next();
    qDebug() << "Object: " << i.name();
    c.setProperty(i.name(), i.value());
    //scriptEngine->globalObject().setProperty(i.name(), i.value());
  }

  return c;
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

bool ScriptUtils::chdir(QString dir) {
  return QDir::setCurrent(dir);
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

QString ScriptUtils::load(QString filename) {
  QFile f(filename);
  f.open(QIODevice::ReadOnly);

  if(!f.exists()) {
    message("File '" + filename +"' not found");
    return QString();
  }

  QTextStream in(&f);
  return in.readAll();
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

  QScriptContext *context = scriptEngine->currentContext();
  QScriptContext *parent = context->parentContext();
  if(parent!=0)
  {
    context->setActivationObject(context->parentContext()->activationObject());
    context->setThisObject(context->parentContext()->thisObject());
  }

  // Change to the directory of the script before running it.
  QFileInfo fileInfo(filename);
  QDir currentDir = QDir::current();
  //QDir::setCurrent(fileInfo.absolutePath());
  //qDebug() << "DIR:" << QDir::currentPath();

  // Run the script
  QScriptValue r = scriptEngine->evaluate(program, filename);

  // Change back to the original directory when finished.
  //QDir::setCurrent(currentDir.absolutePath());

  if(scriptEngine->hasUncaughtException()) {
    cprint(filename + ": " + QString::number(scriptEngine->uncaughtExceptionLineNumber()) + ": " +
            scriptEngine->uncaughtException().toString());
    qDebug() << filename << ": " << QString::number(scriptEngine->uncaughtExceptionLineNumber()) << ": " <<
                scriptEngine->uncaughtException().toString();
    scriptEngine->clearExceptions();
  }

  return r;
}

QScriptValue ScriptUtils::loadJSON(QString filename) {
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
  program = '(' + program + ')';

  QScriptContext *context = scriptEngine->currentContext();
  QScriptContext *parent = context->parentContext();
  if(parent!=0)
  {
    context->setActivationObject(context->parentContext()->activationObject());
    context->setThisObject(context->parentContext()->thisObject());
  }

  // Change to the directory of the script before running it.
  QFileInfo fileInfo(filename);
  QDir currentDir = QDir::current();
  //QDir::setCurrent(fileInfo.absolutePath());
  //qDebug() << "DIR:" << QDir::currentPath();

  // Run the script
  QScriptValue r = scriptEngine->evaluate(program, filename, 1);

  // Change back to the original directory when finished.
  //QDir::setCurrent(currentDir.absolutePath());

  if(scriptEngine->hasUncaughtException()) {
    cprint(filename + ": " + QString::number(scriptEngine->uncaughtExceptionLineNumber()) + ": " +
            scriptEngine->uncaughtException().toString());
    qDebug() << filename << ": " << QString::number(scriptEngine->uncaughtExceptionLineNumber()) << ": " <<
                scriptEngine->uncaughtException().toString();
    scriptEngine->clearExceptions();
  }

  return r;
}

// Ideally, the components should be loaded at start time instad of when created.
// This is mostly just to make sure it works.
QScriptValue ScriptUtils::createComponent(QString filename) {
  QDeclarativeComponent * c = new QDeclarativeComponent(mapBox->engine(), filename, mapBox->engine());
  if(c->status() == QDeclarativeComponent::Error) {
      qDebug() << "COMPONENT ERROR: " << c->errors();
  }

  //QObject * item = c->create();
  //QGraphicsItem * o = qobject_cast<QGraphicsObject *>(item);
  //mapBox->mapScene->addItem(o);

  QScriptValue scriptObject = scriptEngine->newQObject(c, QScriptEngine::ScriptOwnership);
  //qDebug() << "ScriptObject values:";
  //dumpScriptObject(scriptObject);
  //qDebug() << "Object children:";
  //qDebug() << item->children();
  //delete c;
  return scriptObject;
}

QScriptValue ScriptUtils::createComponent(QString filename, QObject * parent) {
  QDeclarativeComponent * c = new QDeclarativeComponent(mapBox->engine(), filename, parent);
  if(c->status() == QDeclarativeComponent::Error) {
    qDebug() << c->errors();
  }
  //QObject * item = c->create();
  //QGraphicsItem * o = qobject_cast<QGraphicsObject *>(item);
  //mapBox->mapScene->addItem(o);
  //delete c;
  return scriptEngine->newQObject(c, QScriptEngine::ScriptOwnership);
}

void ScriptUtils::dumpScriptObject(QScriptValue objectValue) {
  QScriptValueIterator i(objectValue);

  while(i.hasNext()) {
    i.next();
    qDebug() << "Object: " << i.name();
    //scriptEngine->globalObject().setProperty(i.name(), i.value());
  }
}

bool ScriptUtils::same(QObject * a, QObject * b) {
  return a == b;
}

void ScriptUtils::dumpObject(QObject * o) {
  qDebug() << o->dynamicPropertyNames();
}

QString ScriptUtils::projectDir() {
  return projDir;
}

QString ScriptUtils::currentDir() {
  return QDir::currentPath();
}

