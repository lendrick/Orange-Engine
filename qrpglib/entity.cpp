#include <QtCore>
#include "globals.h"
#include "sprite.h"
#include "entity.h"
#include "resource.h"
#include "mapbox.h"
#include "player.h"
#include "collisiontester.h"
#include "npc.h"
#include "talkbox.h"
#include "scripttab.h"

Entity::Entity(QString newname, QObject * parent) : QObject(parent) {
  init();
  if(entitynames.contains(newname)) {
    throw("An entity named '" + newname + "' already exists.");
  }

  name = newname;
  id = entities.size();
  entities.push_back(this);
  entitynames[name] = id;
  thisEntity = new Resource(Resource::Entity, id, name, entityfolder);
  setObjectName(name);

  scriptObject = scriptEngine->newQObject(this);
}

Entity::Entity(const Entity & e) {
  init();
  name = e.name + ".copy";
  state = e.state;
  sprite = e.sprite;
  x = e.x;
  y = e.y;
  layer = e.layer;
  solid = e.solid;
  map = e.map;

  for(int i = 0; i < e.getScriptCount(); i++) {
    int x1, y1, x2, y2;
    x1 = y1 = x2 = y2 = 0;
    if(!e.usesDefaultBounds(i))
      e.getScriptBoundingBox(i, x1, y1, x2, y2);

    addScript(e.getScriptCondition(i), e.getScript(i), e.usesDefaultBounds(i), x1, y1, x2, y2);
  }

  id = entities.size();
  entities.push_back(this);
  thisEntity = new Resource(Resource::Entity, id, name, entityfolder);
  setObjectName(name);

  scriptObject = scriptEngine->newQObject(this);
}

Entity::~Entity() {
  if(map) map->RemoveEntity(this->layer, this);
  if(entitynames.contains(name) && entitynames[name] == id) 
    entitynames.remove(name);

  if(id) entities[id] = 0;
  if(thisEntity) delete thisEntity;
}

QScriptValue & Entity::getScriptObject() {
  return scriptObject;
}

void Entity::init() {
  map = 0;
  state = 0;
  frame = 0;
  sprite = 0;
  x = y = 0;
  layer = 0;
  id = 0;
  solid = false;
  touched = activated = false;
  starting = true;
  thisEntity = 0;
}

int Entity::getId() {
  return id;
}

void Entity::setName(QString newname) {
  name = newname;
  thisEntity->setText(0, name);
}

void Entity::draw(double x_offset, double y_offset, double opacity) {
  if(sprite) sprite->Draw(state, apptime.elapsed(), (int) (x - x_offset), (int) (y - y_offset), opacity);
}

void Entity::update() {
  // Execute scripts.
  for(int i = 0; i < scripts.size(); i++) {
    bool execute = false;
    EntityScript * s = &(scripts[i]);
    if(starting && s->condition == ScriptCondition::Start) {
      execute = true;
    } else if(s->condition == ScriptCondition::Touch || s->condition == ScriptCondition::Activate) {
      double x1, y1, x2, y2;
      double px1, py1, px2, py2;
      player->getRealBoundingBox(px1, py1, px2, py2);
      if(s->useDefaultBounds) {
        getRealBoundingBox(x1, y1, x2, y2);
        x1--;
        y1--;
        x2++;
        y2++;
      } else {
        getRealScriptBoundingBox(i, x1, y1, x2, y2);
      }

      if(s->condition == ScriptCondition::Touch) {
        s->wasTouching = s->isTouching;
        s->isTouching = CollisionTester::stationaryTest(x1, y1, x2, y2, px1, py1, px2, py2);
        if(s->isTouching && !s->wasTouching) execute = true;
      } else if(player->isActivated() && s->condition == ScriptCondition::Activate) {
        execute = CollisionTester::stationaryTest(x1, y1, x2, y2, px1, py1, px2, py2);
      }
    //} else if(activated && scripts[i].condition == ScriptCondition::Activate) {
    } else if(s->condition == ScriptCondition::EveryFrame) {
      execute = true;
    }

    //push context
    if(execute) {
      //cprint("execute: " + s->script + "\n");
      QScriptContext * context = scriptEngine->pushContext();
      Npc * n = dynamic_cast< Npc * >(this);
      context->setThisObject(scriptObject);
      scriptEngine->evaluate(s->script);

      if(scriptEngine->hasUncaughtException()) 
        message(scriptEngine->uncaughtException().toString());

      scriptEngine->popContext();
    }
  }
  
  starting = touched = activated = false;
}

int Entity::getState() {
  return state;
}

QString Entity::getStateName() {
  return sprite->GetStateName(state);
}

void Entity::setState(int newState) {
  state = newState;
}

Sprite * Entity::getSprite() {
  return sprite;
}

void Entity::setSprite(Sprite * newSprite) {
  sprite = newSprite;
}

void Entity::setSprite(QString s) {
  sprite = sprites[spritenames[s]];
}

double Entity::getX() {
  return x;
}

double Entity::getY() {
  return y;
}

void Entity::setX(double newX) {
  x = newX;
}

void Entity::setY(double newY) {
  y = newY;
}

void Entity::setPos(double newX, double newY) {
  x = newX;
  y = newY;
}

void Entity::movePos(double dx, double dy) {
  x += dx;
  y += dy;
}

QString Entity::getName() {
  return name;
}

void Entity::move(double dx, double dy) {
  double mx, my;
  mx = my = 0;
  QList < Entity * > touching;
  //cprint("Move: " + QString::number(dx) + ", " + QString::number(dy));
  if(solid) {
    CollisionTester::test(this, dx, dy, mx, my, touching);
  }

  for(int i = 0; i < touching.size(); i++) {
    //cprint("Touching " + touching[i]->getName());
    touching[i]->touch();
  }

  x += dx;
  y += dy;

  //cprint("Additional move: " + QString::number(mx) + ", " + QString::number(my) + " - " + QString::number(fabs(mx) + fabs(my)));
  if(mx || my) {
    //cprint("Additional move: " + QString::number(mx) + ", " + QString::number(my));
    move(mx, my);
  }
}

void Entity::addToMap(int layer) {
  map = mapBox->GetMap();
  map->RemoveEntity(this->layer, this);
  map->AddEntity(layer, this);
  this->layer = layer;
}

int Entity::getLayer() {
  return layer;
}

Map * Entity::getMap() {
  return map;
}

void Entity::getBoundingBox(int & x1, int & y1, int & x2, int & y2) {
  if(sprite) 
    sprite->GetBoundingBox(x1, y1, x2, y2);
  else
    x1 = y1 = x2 = y2 = 0;
}

void Entity::getRealBoundingBox(double & x1, double & y1, double & x2, double & y2) {
  int x1i, y1i, x2i, y2i;
  if(sprite) 
    sprite->GetBoundingBox(x1i, y1i, x2i, y2i);
  else
    x1 = y1 = x2 = y2 = 0;

  x1 = ((double) x1i) + x;
  y1 = ((double) y1i) + y;
  x2 = ((double) x2i) + x;
  y2 = ((double) y2i) + y;
}

void Entity::getRealScriptBoundingBox(int index, double & x1, double & y1, double & x2, double & y2) const {
  int x1i, y1i, x2i, y2i;
  getScriptBoundingBox(index, x1i, y1i, x2i, y2i);

  x1 = ((double) x1i) + x;
  y1 = ((double) y1i) + y;
  x2 = ((double) x2i) + x;
  y2 = ((double) y2i) + y;
}

void Entity::getSpriteBox(int & x1, int & y1, int & x2, int & y2) {
  if(sprite) {
    int w, h, xo, yo;
    Bitmap * b = sprite->GetTileset();
    if(b) {
      b->GetSize(w, h);
      sprite->GetOrigin(xo, yo);
      x1 = -xo;
      y1 = -yo;
      x2 = w - xo;
      y2 = h - yo;
    } else {
      x1 = y1 = x2 = y2 = 0;
    }
  } else {
    x1 = y1 = x2 = y2 = 0;
  }
}

void Entity::getRealSpriteBox(double & x1, double & y1, double & x2, double & y2) {
  int x1i, y1i, x2i, y2i;
  getSpriteBox(x1i, y1i, x2i, y2i);

  x1 = ((double) x1i) + x;
  y1 = ((double) y1i) + y;
  x2 = ((double) x2i) + x;
  y2 = ((double) y2i) + y;
}

void Entity::start() {
  starting = true;
}

void Entity::touch() {
  touched = true;
}

void Entity::activate() {
  activated = true;
}

void Entity::setSolid(bool s) {
  solid = s;
}

bool Entity::isSolid() {
  return solid;
}

void Entity::addScript(int cond, QString scr, bool useDefaultBounds, int x1, int y1, int x2, int y2) {
  scripts.append(EntityScript(cond, scr, useDefaultBounds, x1, y1, x2, y2));
}

void Entity::clearScripts() {
  scripts.clear();
}

int Entity::getScriptCount() const {
  return scripts.size();
}

QString Entity::getScript(int index) const {
  return scripts[index].script;
}

int Entity::getScriptCondition(int index) const {
  return scripts[index].condition;
}

bool Entity::usesDefaultBounds(int index) const {
  return scripts[index].useDefaultBounds;
}

void Entity::getScriptBoundingBox(int index, int & x1, int & y1, int & x2, int & y2) const {
  x1 = scripts[index].x1;
  y1 = scripts[index].y1;
  x2 = scripts[index].x2;
  y2 = scripts[index].y2;
}


bool entity_y_order(Entity * a, Entity * b) {
  if(a->getY() < b->getY()) return true;
  return false;
}

void Entity::say(QString s) {
  //cprint("Saying: " + s + "\n");
  TalkBox * t = new TalkBox(s);
}

EntityScript::EntityScript(int c, QString s, bool u, int nx1, int ny1, int nx2, int ny2) { 
  condition = c; 
  script = s; 
  useDefaultBounds = u;
  x1 = nx1;
  y1 = ny1;
  x2 = nx2;
  y2 = ny2;
  wasTouching = false;
  isTouching = false;
};
