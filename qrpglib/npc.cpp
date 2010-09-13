#include <QtCore>
#include "input.h"
#include "entity.h"
#include "npc.h"
#include "math.h"
#include "globals.h"
#include <iostream>

Npc::Npc(QString newName, QObject * parent) : Entity(newName, parent) {
  currentMove = 0;
  defaultSpeed = 64;
  solid = true;
  cprint("Creating NPC '" + newName + "'");
  scriptObject = scriptEngine->newQObject(this);
}

Npc::Npc(const Npc & n) : Entity(n) {
  defaultSpeed = n.defaultSpeed;

  if(n.currentMove) 
    currentMove = new MoveQueueItem(*(n.currentMove));
  else
    currentMove = 0;

  for(int i = 0; i < n.moveQueue.size(); i++) {
    MoveQueueItem * move = new MoveQueueItem(*(n.moveQueue[i]));
    moveQueue.append(move);
  }

  scriptObject = scriptEngine->newQObject(this);
}

Entity * Npc::clone() {
  return new Npc(*this);
}

void Npc::update() {
  Entity::update();

  // Follow the currently queued item.
  if(!currentMove && !moveQueue.isEmpty()) 
    currentMove = moveQueue.takeFirst();
  
  if(currentMove) {
    if(currentMove->type == MoveItem) {
      // Normalize movement vector and multiply by speed
      if(!currentMove->started) {
        currentMove->started = true;
        if(abs(currentMove->dy) > abs(currentMove->dx)) {
          if(currentMove->dy < 0) state = 1;
          else state = 0;
        } else {
          if(currentMove->dx < 0) state = 2;
          else state = 3;
        }
      }
      
      double m = sqrt(pow(currentMove->dx, 2.0) + pow(currentMove->dy, 2.0));
      double x = 0.0;
      double y = 0.0;
      if(m > 0.0) {
        x = (currentMove->dx / m) * currentMove->speed * timeSinceLastFrame;
        y = (currentMove->dy / m) * currentMove->speed * timeSinceLastFrame;
      }   
      
      // don't overshoot if speed is larger than next move
      if(fabs(x) >= fabs(currentMove->dx) && fabs(y) >= fabs(currentMove->dy) ) {
        x = currentMove->dx;
        y = currentMove->dy;
      }
      
      currentMove->dx -= x;
      currentMove->dy -= y;
      
      move(x, y);
      
      if(currentMove->dx == 0 && currentMove->dy == 0) {
        delete currentMove;
        currentMove = 0;
      }
    } else if(currentMove->type == WaitItem) {
      currentMove->wait -= timeSinceLastFrame;
      if(currentMove->wait <= 0) {
        delete currentMove;
        currentMove = 0;
      }
    } else if(currentMove->type == ScriptItem) {
      cprint("Evaluating script: " + currentMove->script);
      QScriptContext * context = scriptEngine->pushContext();
      context->setThisObject(scriptObject);
      scriptEngine->evaluate(currentMove->script);
      if(scriptEngine->hasUncaughtException()) 
        message(scriptEngine->uncaughtException().toString());
      scriptEngine->popContext();
      delete currentMove;
      currentMove = 0;
    }
  }
}

void Npc::queueMoveTo(double x, double y, double speed) {
  if(!speed) speed = defaultSpeed;
  x -= this->x;
  y -= this->y;
  queueMove(x, y, speed);
}

void Npc::queueMove(double x, double y, double speed) {
  if(!speed) speed = defaultSpeed;
  moveQueue.push_back(new MoveQueueItem(x, y, speed / 1000.0));
}

void Npc::queueWait(int w) {
  moveQueue.push_back(new MoveQueueItem(w * 1000));
}

void Npc::queueScript(QString s) {
  moveQueue.push_back(new MoveQueueItem(s));
}

void Npc::clearQueue() {
  delete currentMove;
  currentMove = 0;
  while(!moveQueue.isEmpty()) 
    delete moveQueue.takeFirst();
}

void Npc::MoveQueueItem::init() {
  dx = dy = speed = 0;
  wait = 0;
  started = false;
}

Npc::MoveQueueItem::MoveQueueItem(double x, double y, double s) {
  init();
  type = MoveItem;
  dx = x;
  dy = y;
  speed = s;
}

Npc::MoveQueueItem::MoveQueueItem(int w) {
  init();
  type = WaitItem;
  wait = w;
}

Npc::MoveQueueItem::MoveQueueItem(QString s) {
  init();
  type = ScriptItem;
  script = s;
}

Npc::MoveQueueItem::MoveQueueItem(const MoveQueueItem & n) {
  init();
  type = n.type;
  dx = n.dx;
  dy = n.dy;
  speed = n.speed;
  script = n.script;
  wait = n.wait;
  started = n.started;
}

QScriptValue npcConstructor(QScriptContext * context, QScriptEngine * engine) {
  QString name = context->argument(0).toString();
  QObject * parent = context->argument(1).toQObject();
  try {
    Npc * object = new Npc(name, parent);
    return engine->newQObject(object, QScriptEngine::QtOwnership);
  } catch(QString s) {
    message(s);
    return QScriptValue(false);
  }
}
