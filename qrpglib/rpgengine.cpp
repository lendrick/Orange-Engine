#include "rpgengine.h"
#include <QtCore>
#include <QtScript>

#include "globals.h"
#include "map.h"
#include "player.h"
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

void RPGEngine::init() {
  int audio_rate = 44100;
  Uint16 audio_format = AUDIO_S16;
  int audio_channels = 2;
  int audio_buffers = 4096;
  rpgEngineStarting = true;

  SDL_Init(SDL_INIT_AUDIO);
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    printf("Mix_OpenAudio: %s\n", Mix_GetError());
    exit(1);
  }
}

void RPGEngine::setCurrentMap(Map * m) {
  currentMap = m;
  if(m)
    scriptEngine->globalObject().setProperty("map", currentMap->getScriptObject());
  else
    scriptEngine->globalObject().setProperty("map", QScriptValue(QScriptValue::NullValue));
}

void RPGEngine::setPlayerEntity(Player * p) {
  playerEntity = p;
  if(p)
    scriptEngine->globalObject().setProperty("player", playerEntity->getScriptObject());
  else
    scriptEngine->globalObject().setProperty("player", QScriptValue(QScriptValue::NullValue));
}

Map * RPGEngine::getCurrentMap() {
  return currentMap;
}

Player * RPGEngine::getPlayerEntity() {
  return playerEntity;
}

void RPGEngine::addScript(int cond, QString scr) {
  globalScripts.append(RPGScript(cond, scr));
}

void RPGEngine::clearScripts() {
  globalScripts.clear();
}

int RPGEngine::getScriptCount() {
  return globalScripts.size();
}

QString RPGEngine::getScript(int index) {
  return globalScripts[index].script;
}

int RPGEngine::getScriptCondition(int index) {
  return globalScripts[index].condition;
}

void RPGEngine::dumpEvent(QEvent * event)
{
  QMetaObject dataObject = event->staticMetaObject;
  int index = dataObject.indexOfEnumerator("Type");
  QMetaEnum enumData = dataObject.enumerator(index);
  if(event->type() != 43)
    qDebug() << "Event: " << enumData.valueToKey(event->type()) << "\n";
}

QString RPGEngine::eventName(QEvent * event)
{
  QMetaObject dataObject = event->staticMetaObject;
  int index = dataObject.indexOfEnumerator("Type");
  QMetaEnum enumData = dataObject.enumerator(index);
  return QString(enumData.valueToKey(event->type()));
}
