#include <QtCore>
#include "input.h"
#include "npc.h"
#include "entity.h"
#include "player.h"
#include "rpgengine.h"
#include "globals.h"

Player::Player() : Npc("Player") {
  solid = true;
  RPGEngine::setPlayerEntity(this);
  defaultSpeed = 100;
  activated = false;
  wasActivated = false;
}

Player::Player(const Player & p) : Npc(p) {
  // nothing to copy here.
}

QSharedPointer<Entity> Player::clone() {
  return QSharedPointer<Entity>(new Player(*this));
}

void Player::update() {
  wasActivated = activated;
  double dx = 0;
  double dy = 0;

  if(input->up) {
    dy -= 1;
    state = 1;
  }

  if(input->down) {
    dy += 1;
    state = 0;
  }

  if(input->left) {
    dx -= 1;
    state = 2;
  }

  if(input->right) {
    dx += 1;
    state = 3;
  }
  
  if(dx || dy) {
    double m = sqrt(pow(dx, 2) + pow(dy, 2));
    dx = dx / m * defaultSpeed;
    dy = dy / m * defaultSpeed;
    move(dx / 1000 * timeSinceLastFrame, dy / 1000 * timeSinceLastFrame);
  }

  Npc::update();
}

bool Player::isActivated() {
  return activated && !wasActivated;
}

void Player::setActivated(bool a) {
  activated = a;
}
