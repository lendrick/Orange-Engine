#ifndef SOUND_H
#define SOUND_H

#include <QtCore>
#include <QtScript>
#include "SDL/SDL.h"
#include "SDL/SDL_mixer.h"

class Sound : public QObject, public QScriptable
{
  Q_OBJECT
public:
  explicit Sound(QObject *parent = 0);
  Sound(QString filename, QObject *parent = 0);

signals:

public slots:
  void play();
  void stop();
  void setLoop(bool);
  void setVolume(int);
  void load(QString filename);
  bool isPlaying();

protected:
  bool playing;
  bool loop;
  Mix_Chunk * chunk;
  int channel;
  int volume;
  QString name;

};

QScriptValue soundConstructor(QScriptContext * context, QScriptEngine * engine);

#endif // SOUND_H
