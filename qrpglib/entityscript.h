#ifndef ENTITYSCRIPT_H
#define ENTITYSCRIPT_H

#include <QtCore>
#include "rpgscript.h"

struct EntityScript : public RPGScript {
  EntityScript(int c, QString s, bool u, int nx1, int ny1, int nx2, int ny2);
  int x1, y1, x2, y2;
  bool useDefaultBounds;
  bool wasTouching, isTouching;
};

#endif // ENTITYSCRIPT_H
