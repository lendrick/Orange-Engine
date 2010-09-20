#ifndef polygon_h
#define polygon_h 1

#include <vector>
#include <list>

struct Vertex {
  int x, y;

  Vertex(int vx, int vy) {
    this->x = vx;
    this->y = vy;
  }
  
  void getPos(int &vx, int &vy) {
    vx = this->x;
    vy = this->y;
  }
};

bool line_intersect(int x1, int y1, int x2, int y2,
		    int X1, int Y1, int X2, int Y2, 
		    int &x, int &y);

class Poly {
public:
  Poly();
  ~Poly();

  void addVertex(Vertex * v);
  void addVertex(int vx, int vy);
  bool isColliding(int mx, int my, std::list< Poly * > * polys);
  bool isColliding(int mx, int my, Poly * p);
  void draw();
  void move(int mx, int my);
  void move(int mx, int my, std::list< Poly * > * polys);
  void setPos(int x, int y);
  void getPos(int &x, int &y);
  void gGetSide(unsigned int s, int &x1, int &y1, int &x2, int &y2);
  bool inside(int px, int py, int mx, int my);

  std::vector<Vertex *> vertices;
  std::vector<Vertex *>::iterator v;

  int bx1, by1, bx2, by2;

  int x, y;
};

#endif
