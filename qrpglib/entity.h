#ifndef ENTITY_H
#define ENTITY_H 1

#include <QtCore>
#include <QtScript>
#include "sprite.h"
#include "resource.h"
#include "rpgscript.h"

struct EntityScript : public RPGScript {
  EntityScript(int c, QString s, bool u, int nx1, int ny1, int nx2, int ny2);
  int x1, y1, x2, y2;
  bool useDefaultBounds;
  bool wasTouching, isTouching;
};

bool entity_y_order(Entity * a, Entity * b);

class Entity : public QObject, public QScriptable {
  Q_OBJECT
public:
  Entity(QString newName = "", QObject * parent = 0);
  Entity(const Entity & e);
  ~Entity();
  void init();
  virtual void update();
  void draw(double x_offset, double y_offset, double opacity = 1.0);
  friend bool entity_y_order(Entity * a, Entity * b);

protected:
  int state;
  int frame;
  int layer;
  Sprite * sprite;
  Map * map;
  Resource * thisEntity;
  double x, y;
  int bx1, by1, bx2, by2;
  QString name;
  bool solid;
  QList < EntityScript > scripts;
  bool touched, activated, starting;
  int id;
  QScriptValue scriptObject;
  bool overrideBoundingBox;
  bool invisible;

public slots:
  virtual Entity * clone() = 0;
  int getState();
  int getId();
  QString getStateName();
  void setState(int);
  Sprite * getSprite();
  Map * getMap();
  void setSprite(Sprite *);
  void setSprite(QString s);
  double getX();
  double getY();
  void setX(double);
  void setY(double);
  void move(double, double);
  void setPos(double, double);
  void setLayer(int);
  void movePos(double, double);
  void setName(QString);
  QString getName();
  void addToMap(int);
  void getBoundingBox(int &, int &, int &, int &);
  void getRealBoundingBox(double &, double &, double &, double &);
  void getSpriteBox(int &, int &, int &, int &);
  void getRealSpriteBox(double &, double &, double &, double &);
  void setSolid(bool);
  bool isSolid();
  void addScript(int, QString, bool useDefaultBounds = true, int x1 = 0, int y1 = 0, int x2 = 0, int y2 = 0);
  void clearScripts();
  int getScriptCount() const;
  QString getScript(int) const;
  int getScriptCondition(int) const;
  bool usesDefaultBounds(int) const;
  void getScriptBoundingBox(int, int &, int &, int &, int &) const;
  void getRealScriptBoundingBox(int, double &, double &, double &, double &) const;
  void say(QString s);
  QScriptValue & getScriptObject();
  bool getOverrideBoundingBox();
  bool isInvisible();
  void setOverrideBoundingBox(bool);
  void setInvisible(bool);
  void setBoundingBox(int, int, int, int);

  void start();
  void touch();
  void activate();

  int getLayer();
};

#endif
