#include "entityscript.h"
#include <QtCore>

EntityScript::EntityScript(int c, QString s,
                           bool u, int nx1, int ny1, int nx2, int ny2)
                             : RPGScript(c, s)
{
  useDefaultBounds = u;
  x1 = nx1;
  y1 = ny1;
  x2 = nx2;
  y2 = ny2;
  wasTouching = false;
  isTouching = false;
};
