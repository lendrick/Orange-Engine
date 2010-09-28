#ifndef PLAYER_H
#define PLAYER_H 1

#include <QtCore>
#include "entity.h"
#include "npc.h"

class Player : public Npc {
  Q_OBJECT
public:
  Player();
  Player(const Player & p);
  virtual void update();
public slots:
  EntityPointer clone();
  bool isActivated();
  void setActivated(bool);
private:
  bool activated, wasActivated;
};


#endif
