#ifndef NPC_H
#define NPC_H 1

#include <QtCore>
#include <QtScript>
#include "entity.h"

class Npc : public Entity {
  Q_OBJECT
public:
  Npc(QString newName, QObject * parent = 0);
  Npc(const Npc & n);
  virtual void update();
  QString name;
public slots:
  void queueMove(double x, double y, double speed = 0);
  void queueMoveTo(double x, double y, double speed = 0);
  void queueWait(int w);
  void queueScript(QString s);
  void clearQueue();
  Entity * clone();
protected:
  double defaultSpeed;
  
  enum QueueItemType {
    MoveItem,
    WaitItem,
    ScriptItem
  };
  
  struct MoveQueueItem {
    MoveQueueItem(double x, double y, double s);
    MoveQueueItem(int w);
    MoveQueueItem(QString s);
    MoveQueueItem(const MoveQueueItem & m);
    QueueItemType type;
    void init();
    bool started;
    double dx;
    double dy;
    double speed;
    int wait;
    QString script;
  };

  MoveQueueItem * currentMove;
  QList < MoveQueueItem * > moveQueue;
};

QScriptValue npcConstructor(QScriptContext * context, QScriptEngine * engine);

#endif