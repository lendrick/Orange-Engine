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
  
  void GetPos(int &vx, int &vy) {
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

  void AddVertex(Vertex * v);
  void AddVertex(int vx, int vy);
  bool IsColliding(int mx, int my, std::list< Poly * > * polys);
  bool IsColliding(int mx, int my, Poly * p);
  void Draw();
  void Move(int mx, int my);
  void Move(int mx, int my, std::list< Poly * > * polys);
  void SetPos(int x, int y);
  void GetPos(int &x, int &y);
  void GetSide(unsigned int s, int &x1, int &y1, int &x2, int &y2);
  bool Inside(int px, int py, int mx, int my);

  std::vector<Vertex *> vertices;
  std::vector<Vertex *>::iterator v;

  int bx1, by1, bx2, by2;

  int x, y;
};

#endif
