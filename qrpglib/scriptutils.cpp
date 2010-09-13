#include <QtCore>
#include <QtScript>
#include "scriptutils.h"
#include "globals.h"
#include "entity.h"
#include "npc.h"

ScriptUtils::ScriptUtils() {  
  QScriptValue objectValue = scriptEngine->newQObject(this);
  scriptEngine->globalObject().setProperty("rpgx", objectValue);

  QScriptValue npcCtor = scriptEngine->newFunction(npcConstructor);
  QScriptValue metaObject = scriptEngine->newQMetaObject(&QObject::staticMetaObject, npcCtor);
  scriptEngine->globalObject().setProperty("Npc", metaObject);
}

void ScriptUtils::messageBox(QString s) {
  message(s);
}

void ScriptUtils::print(QString s) {
  cprint(s);
}

QScriptValue ScriptUtils::getEntity(QString s) {
  Entity * e = entities[mapentitynames[s]];
  return e->getScriptObject();
}
