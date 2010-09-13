#ifndef COLLISIONTESTER_H
#define COLLISIONTESTER_H 1

#include <QtCore>

class Map;
class Entity;

class CollisionTester {
public:
  static bool test(Entity * entity, double &dx, double &dy, double & mx, double &my, QList < Entity * > & touching);


  static bool stationaryTest(
    double x1, double y1, double x2, double y2,
    double tx1, double ty1, double tx2, double ty2
  );

private:
  struct CollisionData {
    double distance;
    double move_x, move_y;
    double dx, dy;
    bool collision;
    bool corner;
    CollisionData();
  };

  static CollisionData boxTest(
    double x1, double y1, double x2, double y2,
    double tx1, double ty1, double tx2, double ty2, 
    double dx, double dy
  );

  static CollisionData entityTest(Entity * a, double dx, double dy, Entity * b);

  static CollisionData tileTest(Entity * entity, double dx, double dy, int tx, int ty, int tw, int th);
  
  static inline void step(double &i, int step, double end);
  static inline double getX(double y, double slope, double x_start, double y_start);
  static inline double getY(double x, double slope, double x_start, double y_start);  
  static inline bool overlap(double a1, double a2, double b1, double b2);
};

#endif
