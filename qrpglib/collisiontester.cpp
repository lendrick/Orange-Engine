#include "collisiontester.h"
#include "entity.h"
#include "map.h"
#include "globals.h"
#include <QtCore>
#include <math.h>
#include <algorithm>

using std::max;
using std::min;

bool CollisionTester::test(Entity * entity, double &dx, double &dy, double &mx, double &my,
                           QList < Entity * > & touching) {
  double x = entity->getX();
  double y = entity->getY();
  bool collision = false;
  //QList < QVector2D > deflections;

  mx = my = 0;

  int tw, th;
  entity->getMap()->getTileSize(tw, th);
  int x1, y1, x2, y2;
  entity->getBoundingBox(x1, y1, x2, y2);
  double distance = fabs(dx) + fabs(dy) + x2 - x1 + y2 - y1;

  //if(dy >= 0 && dx >= 00) {
  double x_start, x_end, y_start, y_end;
  if(dx > 0) {
    x_start = x + x1;
    x_end = x + dx + x2;
  } else {
    x_start = x + dx + x1;
    x_end = x + x2;
  }

  if(dy > 0) {
    y_start = y + y1;
    y_end = y + dy + y2;
  } else {
    y_start = y + dy + y1;
    y_end = y + y2;
  }
  
  double ndx = dx;
  double ndy = dy;

  for(int j = min(y_start, y_end) / th; j <= max(y_start, y_end) / th; j++) {
    for(int i = min(x_start, x_end) / tw; i <= max(x_start, x_end) / tw; i++) {
      //cprint(QString::number(i) + ", " + QString::number(j));
      CollisionData c = tileTest(entity, dx, dy, i, j, tw, th);
      if(c.collision && c.distance <= distance) {
        //cprint("  " + QString::number(c.distance) + " <= " + QString::number(distance));
        distance = c.distance;
        collision = true;
        /*
        if(mx || my) {
          deflections.append(QVector2D(mx, my));
        }
        */
        if(!c.corner) {
          mx = c.move_x;
          my = c.move_y;
        }
        if(sqrt(pow(ndx, 2) + pow(ndy, 2)) > sqrt(pow(c.dx, 2) + pow(c.dy, 2))) {
          ndx = c.dx;
          ndy = c.dy;
        }
        //dx = c.dx;
        //dy = c.dy;
        //cprint("*");
      }
    }
  }

  for(int i = 0; i < entity->getMap()->getEntities(entity->getLayer()); i++) {
    Entity * b = entity->getMap()->getEntity(entity->getLayer(), i);
    if(entity == b) continue;
    CollisionData c = entityTest(entity, dx, dy, b);
    if(c.collision && c.distance <= distance) {
      if(c.distance < distance) touching.clear();
      touching.append(b);
      distance = c.distance;
      collision = true;
      if(!c.corner) {
        mx = c.move_x;
        my = c.move_y;
      }
      if(sqrt(pow(ndx, 2) + pow(ndy, 2)) > sqrt(pow(c.dx, 2) + pow(c.dy, 2))) {
        ndx = c.dx;
        ndy = c.dy;
      }
    }
  }
  
  dx = ndx;
  dy = ndy;
  
  //cprint(" Moving: " + QString::number(dx) + ", " + QString::number(dy));
  //cprint(" Deflected: " + QString::number(mx) + ", " + QString::number(my));
  
  //TODO:
  //A better way to do this would be to get a list of *all* of the possible 
  //deflection vectors and then go with the first viable one.  This way causes
  //things to freeze up on corners, which is bad.
  //A temporary solution is to make sure bounding boxes aren't exactly the same 
  //size as tiles.
  return collision;
}

bool CollisionTester::stationaryTest(
  double x1, double y1, double x2, double y2,
  double tx1, double ty1, double tx2, double ty2)
{
  return(overlap(x1, x2, tx1, tx2) && overlap(y1, y2, ty1, ty2));
}

CollisionTester::CollisionData CollisionTester::boxTest(
  double x1, double y1, double x2, double y2,
  double tx1, double ty1, double tx2, double ty2, 
  double dx, double dy) 
{
  CollisionData c;
  bool horizontal = true;
  bool vertical = true;

  double xstart, ystart, xend, yend, start, end;

  if(dx > 0) {
    xstart = (tx1 - x2) / dx;
    xend = (tx2 - x1) / dx;
  } else {
    xstart = (tx2 - x1) / dx;
    xend = (tx1 - x2) / dx;
  }

  if(dy > 0) {
    ystart = (ty1 - y2) / dy;
    yend = (ty2 - y1) / dy;
  } else {
    ystart = (ty2 - y1) / dy;
    yend = (ty1 - y2) / dy;
  }

  start = 1;
  end = 0;
  if(dx && dy) {
    start = max(xstart, ystart);
    end = min(xend, yend);
  } else if(dx && overlap(y1, y2, ty1, ty2)) {
    start = xstart;
    end = xend;
    vertical = false;
  } else if(dy && overlap(x1, x2, tx1, tx2)) {
    start = ystart;
    end = yend;
    horizontal = false;
  }
  
  if(start == xstart) horizontal = false;
  if(start == ystart) vertical = false;

  if(end <= start) return c;
  if(start >=  1) return c;
  if(end <= 0) return c;

  if(start < 0) start = 0;
  c.collision = true;
  c.dx = dx * start;
  c.dy = dy * start;
  c.distance = sqrt(pow(c.dx, 2) + pow(c.dy, 2));

  if(horizontal)
    c.move_x = dx - c.dx;
  if(vertical)
    c.move_y = dy - c.dy;
  
  if(!horizontal && !vertical) c.corner = true;

  return c;
}

CollisionTester::CollisionData CollisionTester::entityTest(
  Entity * a, double dx, double dy, Entity * b) 
{
  double x1, y1, x2, y2;
  double tx1, ty1, tx2, ty2;

  a->getRealBoundingBox(x1, y1, x2, y2);
  b->getRealBoundingBox(tx1, ty1, tx2, ty2);

  return boxTest(x1, y1, x2, y2, tx1, ty1, tx2, ty2, dx, dy);
}

CollisionTester::CollisionData CollisionTester::tileTest(Entity * entity, double dx, double dy, int tx, int ty, int tw, int th) {
  CollisionData c;

  double x1, y1, x2, y2;
  double tx1, ty1, tx2, ty2;

  if(entity->getMap()->getTile(entity->getLayer(), tx, ty) == 0) return c;
  entity->getRealBoundingBox(x1, y1, x2, y2);

  // get tile coordinates
  tx1 = tx * tw;
  ty1 = ty * th;
  tx2 = tx * tw + tw;
  ty2 = ty * th + th;

  return boxTest(x1, y1, x2, y2, tx1, ty1, tx2, ty2, dx, dy);
  

  /*
  CollisionData c;
  bool horizontal = true;
  bool vertical = true;

  // Skip empty tiles
//  cprint("tileTest: " + QString::number(tx) + ", " + QString::number(ty) + " (" +
//  QString::number(dx) + ", " + QString::number(dy) + ")");
  if(entity->getMap()->GetTile(entity->getLayer(), tx, ty) == 0) return c;
  
  double x = entity->getX();
  double y = entity->getY();  
  double x1, y1, x2, y2;
  double tx1, ty1, tx2, ty2;

  entity->getRealBoundingBox(x1, y1, x2, y2);

  // get tile coordinates
  tx1 = tx * tw;
  ty1 = ty * th;
  tx2 = tx * tw + tw;
  ty2 = ty * th + th;

  
//  cprint(" - (" + QString::number(x1) + ", " + QString::number(y1) + ") ("
//    + QString::number(x2) + ", " + QString::number(y2) + ") - (" 
//    + QString::number(tx1) + ", " + QString::number(ty1) + ") ("
//    + QString::number(tx2) + ", " + QString::number(ty2) + ")");
    

  double xstart, ystart, xend, yend, start, end;

  if(dx > 0) {
    xstart = (tx1 - x2) / dx;
    xend = (tx2 - x1) / dx;
  } else {
    xstart = (tx2 - x1) / dx;
    xend = (tx1 - x2) / dx;
  }

  if(dy > 0) {
    ystart = (ty1 - y2) / dy;
    yend = (ty2 - y1) / dy;
  } else {
    ystart = (ty2 - y1) / dy;
    yend = (ty1 - y2) / dy;
  }

  //start = max(min(xstart, xend), min(ystart, yend));
  //end = min(max(xstart, xend), max(ystart, yend));
  start = 1;
  end = 0;
  if(dx && dy) {
//    cprint(" -- X: " + QString::number(xstart) + " --> " + QString::number(xend));
//    cprint(" -- Y: " + QString::number(ystart) + " --> " + QString::number(yend));
    start = max(xstart, ystart);
    end = min(xend, yend);
  } else if(dx && overlap(y1, y2, ty1, ty2)) {
//    cprint(" -- X: " + QString::number(xstart) + " --> " + QString::number(xend));
    start = xstart;
    end = xend;
    vertical = false;
  } else if(dy && overlap(x1, x2, tx1, tx2)) {
//    cprint(" -- Y: " + QString::number(ystart) + " --> " + QString::number(yend));
    start = ystart;
    end = yend;
    horizontal = false;
  }
  
//  cprint(" --- T: " + QString::number(start) + " --> " + QString::number(end));
  if(start == xstart) horizontal = false;
  if(start == ystart) vertical = false;

  if(end <= start) return c;
  if(start >=  1) return c;
  if(end <= 0) return c;

  if(start < 0) start = 0;
  c.collision = true;
  c.dx = dx * start;
  c.dy = dy * start;
  c.distance = sqrt(pow(c.dx, 2) + pow(c.dy, 2));

  // TODO: 
  if(horizontal)
    c.move_x = dx - c.dx;
  if(vertical)
    c.move_y = dy - c.dy;
  
  if(!horizontal && !vertical) c.corner = true;

//  cprint(" --- COLLISION: " + QString::number(start));
  //if(c.corner) cprint("(corner)");
//  cprint(" --- deflection: (" + QString::number(c.move_x) + ", " +
//    QString::number(c.move_y) + ")");
  return c;
  */
}

void CollisionTester::step(double &i, int step, double end) {
  int t = i / step;
  i = (t + 1) * step;
  if(i > end) i = end;
}

double CollisionTester::getX(double y, double slope, double x_start, double y_start) {
  double x = 0;
  y -= y_start;
  if(slope != 0) x = y / slope;
  return x + x_start;
}

double CollisionTester::getY(double x, double slope, double x_start, double y_start) {
  return (x - x_start) * slope + y_start;
}

CollisionTester::CollisionData::CollisionData() {
  distance = move_x = move_y = dx = dy = 0;
  collision = false;
  corner = false;
}

bool CollisionTester::overlap(double a1, double a2, double b1, double b2) {
  if(a1 > min(b1, b2) && a1 < max(b1, b2)) return true;
  if(a2 > min(b1, b2) && a2 < max(b1, b2)) return true;
  if(b1 > min(a1, a2) && b1 < max(a1, a2)) return true;
  if(min(a1, a2) == min(b1, b2)) return true;
  if(max(a1, a2) == max(b1, b2)) return true;
  return false;
}