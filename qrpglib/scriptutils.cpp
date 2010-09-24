#include <QtCore>
#include <QtScript>
#include "scriptutils.h"
#include "globals.h"
#include "map.h"
#include "entity.h"
#include "npc.h"
#include "player.h"
#include "mapbox.h"
#include "sound.h"

ScriptUtils::ScriptUtils() {  
  QScriptValue objectValue = scriptEngine->newQObject(this);
  scriptEngine->globalObject().setProperty("rpgx", objectValue);

  QScriptValue npcCtor = scriptEngine->newFunction(npcConstructor);
  QScriptValue metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, npcCtor);
  scriptEngine->globalObject().setProperty("Npc", metaObject);

  QScriptValue soundCtor = scriptEngine->newFunction(soundConstructor);
  metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, soundCtor);
  scriptEngine->globalObject().setProperty("Sound", metaObject);
}

void ScriptUtils::messageBox(QString s) {
  message(s);
}

void ScriptUtils::print(QString s) {
  cprint(s);
}

QScriptValue ScriptUtils::getEntity(QString s) {
  QSharedPointer<Entity> e = entities[mapentitynames[s]];
  return e->getScriptObject();
}

QScriptValue ScriptUtils::teleport(QString map, int x, int y) {
  return QScriptValue(QScriptValue::NullValue);
}

void ScriptUtils::setCamera(QSharedPointer<Entity> e) {
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
