#ifndef ENTITY_H
#define ENTITY_H 1

#include <QtCore>
#include <QtScript>
#include "entityscript.h"
#include "sprite.h"
#include "map.h"
#include "resource.h"

typedef QSharedPointer<Entity> EntityPointer;
typedef QSharedPointer<QObject> ObjectPointer;

Q_DECLARE_METATYPE(EntityPointer);

class Entity : public QObject, public QScriptable {
  Q_OBJECT
public:
  Entity(QString newName, bool dynamic = false);
  Entity(const Entity & e);
  ~Entity();
  void init();
  virtual void update();
  void draw(double x_offset, double y_offset, double opacity = 1.0, bool boundingbox = false);
  static bool entity_y_order(EntityPointer a, EntityPointer b);

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
  EntityPointer sharedPointer;
  bool overrideBoundingBox;
  bool invisible;
  bool dynamic;

public slots:
  virtual EntityPointer clone() = 0;
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
  void destroy();
  EntityPointer getSharedPointer();
  QString toXml();

  void start();
  void touch();
  void activate();

  int getLayer();
};

extern QList < EntityPointer > entities;

QScriptValue entityPointerToScriptValue(QScriptEngine * engine, const EntityPointer &p);
void entityPointerFromScriptValue(const QScriptValue &obj, EntityPointer &p);


#endif
