#include <QtCore>
#include <QtScript>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"
#include "sound.h"
#include "globals.h"

Sound::Sound(QObject *parent) :
    QObject(parent)
{
  chunk = 0;
  loop = false;
}

Sound::Sound(QString filename, QObject * parent) : QObject(parent)
{
  chunk = 0;
  loop = false;
  channel = 0;
  volume = 100;
  load(filename);
}

void Sound::play()
{
  cprint("Playing sound '" + name + "'");
  if(chunk) {
    int loops = 0;
    if(loop) loops = -1;

    channel = Mix_PlayChannel(-1, chunk, loops);
    Mix_Volume(channel, volume);
  }
}

void Sound::stop()
{
  cprint("Stopping sound '" + name + "'");
  Mix_HaltChannel(channel);
}

void Sound::setLoop(bool l)
{
  loop = l;
}

void Sound::setVolume(int v)
{
  volume = v;
}

void Sound::load(QString filename)
{
  cprint("Loading sound '" + filename + "'");
  name = filename;
  if(chunk) Mix_FreeChunk(chunk);
  chunk = Mix_LoadWAV(filename.toAscii());
  if(!chunk) {
    throw QString(sprintf("Mix_LoadWAV: %s\n", Mix_GetError()));
  }
}

QScriptValue soundConstructor(QScriptContext * context, QScriptEngine * engine) {
  QString name = context->argument(0).toString();
  QObject * parent = context->argument(1).toQObject();
  try {
    Sound * object = new Sound(name, parent);
    return engine->newQObject(object, QScriptEngine::QtOwnership);
  } catch(QString s) {
    return context->throwError(s);
  }
}


