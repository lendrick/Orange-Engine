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
#include "rpgscript.h"

Entity::Entity(QString newname, bool dynamic) : QObject() {
  init();
  if(dynamic && entityNames.contains(newname)) {
    throw("An entity named '" + newname + "' already exists.");
  } else if(!dynamic && staticEntityNames.contains(newname)) {
    throw("An entity named '" + newname + "' already exists.");
  }

  name = newname;
  id = entities.size();
  sharedPointer = EntityPointer(this);
  entities.push_back(sharedPointer);
  if(dynamic)
    entityNames[name] = id;
  else
    staticEntityNames[name] = id;
  thisEntity = new Resource(Resource::Entity, id, name, entityfolder);
  setObjectName(name);

  scriptObject = scriptEngine->newQObject(this);
}

Entity::Entity(const Entity & e) : QObject(), QScriptable() {
  init();
  name = e.name;
  while(entityNames.contains(name))
    name += ".copy";

  dynamic = true;
  state = e.state;
  sprite = e.sprite;
  x = e.x;
  y = e.y;
  layer = e.layer;
  solid = e.solid;
  map = e.map;

  foreach(const QByteArray & p, e.dynamicPropertyNames()) {
    this->setProperty(p, e.property(p));
  }


  for(int i = 0; i < e.getScriptCount(); i++) {
    int x1, y1, x2, y2;
    x1 = y1 = x2 = y2 = 0;
    if(!e.usesDefaultBounds(i))
      e.getScriptBoundingBox(i, x1, y1, x2, y2);

    addScript(e.getScriptCondition(i), e.getScript(i), e.usesDefaultBounds(i), x1, y1, x2, y2);
  }

  id = entities.size();
  sharedPointer = EntityPointer(this);
  entities.push_back(sharedPointer);
  thisEntity = new Resource(Resource::Entity, id, name, entityfolder);
  setObjectName(name);

  scriptObject = scriptEngine->newQObject(this);
}

void Entity::destroy() {
  if(map) map->removeEntity(this->layer, sharedPointer);
  if(entityNames.contains(name) && entityNames[name] == id)
    entityNames.remove(name);

  if(id) entities[id] = EntityPointer();
  //if(thisEntity) delete thisEntity;

}

Entity::~Entity() {
  destroy();
}

QScriptValue & Entity::getScriptObject() {
  return scriptObject;
}

void Entity::init() {
  //map = 0;
  state = 0;
  frame = 0;
  //sprite = 0;
  x = y = 0;
  bx1 = by1 = bx2 = by2 = 0;
  layer = 0;
  id = 0;
  solid = false;
  touched = activated = false;
  starting = true;
  overrideBoundingBox = false;
  invisible = false;
  //thisEntity = 0;
}

int Entity::getId() {
  return id;
}

void Entity::setName(QString newname) {
  name = newname;
  thisEntity->setText(0, name);
}

void Entity::draw(double x_offset, double y_offset, double opacity, bool boundingbox) {
  if(sprite)
    sprite->draw(state, apptime.elapsed(), (int) (x - x_offset), (int) (y - y_offset), opacity);

  // If we're drawing bounding boxes, or we're in the editor and there's no visible sprite, draw
  // a bounding box

  if(boundingbox || (!play && !sprite)) {
    int x1, y1, x2, y2;
    getBoundingBox(x1, y1, x2, y2);
    glColor4f(0.4, 0.4, 0.8, 0.5);
    glBegin(GL_QUADS);
    glVertex3f(x + x1 - x_offset, y + y1 - y_offset, 0);
    glVertex3f(x + x2 - x_offset, y + y1 - y_offset, 0);
    glVertex3f(x + x2 - x_offset, y + y2 - y_offset, 0);
    glVertex3f(x + x1 - x_offset, y + y2 - y_offset, 0);
    glEnd();
  }
}

void Entity::update() {
  // Execute scripts.
  for(int i = 0; i < scripts.size(); i++) {
    bool execute = false;
    EntityScript * s = &(scripts[i]);
    if(starting && s->condition == ScriptCondition::Load) {
      execute = true;
    } else if(s->condition == ScriptCondition::Enter ||
              s->condition == ScriptCondition::Activate ||
              s->condition == ScriptCondition::Exit) {
      double x1, y1, x2, y2;
      double px1, py1, px2, py2;
      playerEntity->getRealBoundingBox(px1, py1, px2, py2);
      if(s->useDefaultBounds) {
        getRealBoundingBox(x1, y1, x2, y2);
        x1--;
        y1--;
        x2++;
        y2++;
      } else {
        getRealScriptBoundingBox(i, x1, y1, x2, y2);
      }

      if(s->condition == ScriptCondition::Enter) {
        s->wasTouching = s->isTouching;
        s->isTouching = CollisionTester::stationaryTest(x1, y1, x2, y2, px1, py1, px2, py2);
        if(s->isTouching && !s->wasTouching) execute = true;
      } else if(playerEntity->isActivated() && s->condition == ScriptCondition::Activate) {
        execute = CollisionTester::stationaryTest(x1, y1, x2, y2, px1, py1, px2, py2);
      } else if(s->condition == ScriptCondition::Exit) {
        s->wasTouching = s->isTouching;
        s->isTouching = CollisionTester::stationaryTest(x1, y1, x2, y2, px1, py1, px2, py2);
        if(!s->isTouching && s->wasTouching) execute = true;
      }
    //} else if(activated && scripts[i].condition == ScriptCondition::Activate) {
    } else if(s->condition == ScriptCondition::EveryFrame) {
      execute = true;
    }

    //push context
    if(execute) {
      //cprint("execute: " + s->script + "\n");
      QScriptContext * context = scriptEngine->pushContext();
      //Npc * n = dynamic_cast< Npc * >(this);
      context->setThisObject(scriptObject);
      scriptEngine->evaluate(s->script);

      if(scriptEngine->hasUncaughtException()) 
        message(scriptEngine->uncaughtException().toString());

      scriptEngine->popContext();
    }
  }
  
  starting = touched = activated = false;
}

void Entity::runUnLoadScripts() {
  for(int i = 0; i < scripts.size(); i++) {
    bool execute = false;
    EntityScript * s = &(scripts[i]);
    if(s->condition == ScriptCondition::UnLoad) {
      execute = true;
    }

    //push context
    if(execute) {
      //cprint("execute: " + s->script + "\n");
      QScriptContext * context = scriptEngine->pushContext();
      //Npc * n = dynamic_cast< Npc * >(this);
      context->setThisObject(scriptObject);
      scriptEngine->evaluate(s->script);

      if(scriptEngine->hasUncaughtException())
        message(scriptEngine->uncaughtException().toString());

      scriptEngine->popContext();
    }
  }
}

int Entity::getState() {
  return state;
}

QString Entity::getStateName() {
  return sprite->getStateName(state);
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
  QList < EntityPointer > touching;
  //cprint("Move: " + QString::number(dx) + ", " + QString::number(dy));
  if(solid) {
    CollisionTester::test(sharedPointer, dx, dy, mx, my, touching);
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
  map = mapBox->getMap();
  map->addEntity(layer, sharedPointer);
}

int Entity::getLayer() {
  return layer;
}

Map * Entity::getMap() {
  return map;
}

void Entity::getBoundingBox(int & x1, int & y1, int & x2, int & y2) {
  if(overrideBoundingBox || !sprite) {
    x1 = bx1;
    y1 = by1;
    x2 = bx2;
    y2 = by2;
  } else {
    sprite->getBoundingBox(x1, y1, x2, y2);
  }
}

void Entity::getRealBoundingBox(double & x1, double & y1, double & x2, double & y2) {
  int x1i, y1i, x2i, y2i;
  /*
  if(sprite) 
    sprite->getBoundingBox(x1i, y1i, x2i, y2i);
  else
    x1 = y1 = x2 = y2 = 0;
  */
  getBoundingBox(x1i, y1i, x2i, y2i);

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
    Bitmap * b = sprite->getTileset();
    if(b) {
      b->getSize(w, h);
      sprite->getOrigin(xo, yo);
      x1 = -xo;
      y1 = -yo;
      x2 = w - xo;
      y2 = h - yo;
    } else {
      getBoundingBox(x1, y1, x2, y2);
    }
  } else {
    getBoundingBox(x1, y1, x2, y2);
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

void Entity::setLayer(int l) {
  layer = l;
}

bool Entity::entity_y_order(EntityPointer a, EntityPointer b) {
  if(a->getY() < b->getY()) return true;
  return false;
}

void Entity::say(QString s) {
  //cprint("Saying: " + s + "\n");
  TalkBoxProxy * t = new TalkBoxProxy(s);
}

bool Entity::getOverrideBoundingBox() {
  return overrideBoundingBox;
}

void Entity::setOverrideBoundingBox(bool b) {
  overrideBoundingBox = b;
}

bool Entity::isInvisible() {
  return invisible;
}

void Entity::setInvisible(bool i) {
  invisible = i;
}

void Entity::setBoundingBox(int x1, int y1, int x2, int y2) {
  bx1 = x1;
  by1 = y1;
  bx2 = x2;
  by2 = y2;
}

EntityPointer Entity::getSharedPointer() {
  return sharedPointer;
}

QString Entity::toXml() {
  QString output;

  QString name = getName();
  int state = getState();
  int x = getX();
  int y = getY();

  QString sprite;

  if(getSprite())
    sprite = getSprite()->getName();

  output += "      <entity name='" + name + "' state='" +
            QString::number(state) + "' x='" + QString::number(x) + "' y='" + QString::number(y) +
            "' bx1='" + QString::number(bx1) +
            "' by1='" + QString::number(by1) + "' bx2='" + QString::number(bx2) +
            "' by2='" + QString::number(by2) + "'";

  if(sprite != "") {
    output += " sprite='" + sprite + "'";
  }

  if(overrideBoundingBox) {
    output += " overrideboundingbox='1'";
  }

  if(invisible) {
    output += " invisible='1'";
  }

  if(solid) {
    output += " solid = '1'";
  }

  output += ">\n";
  output += "        <scripts>\n";
  for(int y = 0; y < getScriptCount(); y++) {
    int cond = getScriptCondition(y);
    int x1, y1, x2, y2;
    x1 = y1 = x2 = y2 = 0;
    bool defCoords = usesDefaultBounds(y);
    if(!defCoords) {
      getScriptBoundingBox(y, x1, y1, x2, y2);
    }

    output += "          <script condition='" + QString::number(cond) + "'";
    if(!defCoords) {
      output += " x1='" + QString::number(x1) + "' y1='" + QString::number(y1) + "'";
      output += " x2='" + QString::number(x2) + "' y2='" + QString::number(y2) + "'";
    }
    output += "><![CDATA[";
    QString s = getScript(y);
    escapeCData(s);
    output += s;
    output += "]]></script>\n";
  }
  output += "        </scripts>\n";
  output += "      </entity>\n";

  return output;
}

QList < EntityPointer > entities;

QScriptValue entityPointerToScriptValue(QScriptEngine * engine, const EntityPointer &p) {
  return p->getScriptObject();
}

void entityPointerFromScriptValue(const QScriptValue &obj, EntityPointer &p) {
  Entity * e = dynamic_cast<Entity *>(obj.toQObject());
  if(e) {
    p = e->getSharedPointer();
  } else {
    p = EntityPointer();
  }
}
