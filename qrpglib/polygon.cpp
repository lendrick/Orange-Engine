#ifdef WIN32
#include <windows.h>
#endif

#include "polygon.h"
#include <GL/gl.h>
#include <iostream>
#include <math.h>
#include <vector>
#include <list>

using std::cout;

Vertex * start = 0;

bool operator< (Vertex v1, Vertex v2) {
  return (fabs((float) (v1.x - start->x)) + fabs((float) (v1.y - start->y))) <
    (fabs((float) (v2.x - start->x)) + fabs((float) (v2.y - start->y)));
}

bool operator== (Vertex v1, Vertex v2) {
  return (v1.x == v2.x) && (v1.y == v2.y);
}

bool operator!= (Vertex v1, Vertex v2) {
  return (v1.x != v2.x) || (v1.y != v2.y);
}

#ifndef WIN32
int min(int a, int b) {
  if(a > b) return b;
  return a;
}

int max(int a, int b) {
  if(a > b) return a;
  return b;
}
#endif

int len(int x1, int y1, int x2, int y2) {
  return (int) sqrt(pow((float) (x2 - x1), 2) + pow((float) (y2 - y1), 2));
}

Poly::Poly() {
  x = 0;
  y = 0;
  bx1 = 0;
  by1 = 0;
  bx2 = 0;
  by2 = 0;
}

Poly::~Poly() {
  int i;  
  for(i = 0; i < vertices.size(); i++) delete vertices[i];
}

void Poly::AddVertex(Vertex * v) {
  vertices.push_back(v);
}

void Poly::AddVertex(int vx, int vy) {
  Vertex * v = new Vertex(vx, vy);
  vertices.push_back(v);

  if(vx < bx1) bx1 = vx;
  if(vy < by1) by1 = vy;
  if(vx > bx2) bx2 = vx;
  if(vy > by2) by2 = vy;
}

bool Poly::IsColliding(int mx, int my, std::list<Poly *> * polys) {
  std::list <Poly *>::iterator poly;

  for(poly = polys->begin(); poly != polys->end(); poly++) {
    if(IsColliding(mx, my, (*poly))) return true;
  }

  return false;
}

bool Poly::IsColliding(int mx, int my, Poly * p) {
  // If bounding boxes don't intersect, return false
  if(bx1 + x + mx> p->bx2 + p->x || bx2 + x + mx< p->bx1 + p->x || 
     by1 + y + my> p->by2 + p->y || by2 + y + my< p->by1 + p->y)
    return false;

  // Check for intersecting sides
  int x1, y1, x2, y2, X1, Y1, X2, Y2, xi, yi;
  unsigned int i, j;
  for(i = 0; i < vertices.size(); i++) {
    this->GetSide(i, x1, y1, x2, y2);
    for(j = 0; j < p->vertices.size(); j++) {
      p->GetSide(j, X1, Y1, X2, Y2);
      if(line_intersect(x1 + mx, y1 + my, x2 + mx, y2 + my, 
      			X1, Y1, X2, Y2, xi, yi))
      	return true;
    }
  };

  // Check if a vertex in this polygon are inside p
  //if(p->Inside(vertices[0]->x + x + mx, vertices[0]->y + y + my, 0, 0)) 
  //return true;

  // Check if a vertex in p are inside this polygon
  //if(Inside(p->vertices[0]->x + p->x, p->vertices[0]->y + p->y, mx, my))
  //return true;

  return false;
}

void Poly::GetSide(unsigned int s, int &x1, int &y1, int &x2, int &y2) {
  x1 = vertices[s]->x + x;
  y1 = vertices[s]->y + y;
  if(s == vertices.size() - 1) {
    x2 = vertices[0]->x + x;
    y2 = vertices[0]->y + y;
  } else {
    x2 = vertices[s+1]->x + x;
    y2 = vertices[s+1]->y + y;
  }
}

void Poly::Draw() {
  glShadeModel(GL_FLAT);
  glDisable(GL_TEXTURE_2D);
  glDisable(GL_LIGHTING);
  glEnable(GL_BLEND);
  glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
  glDisable(GL_LINE_SMOOTH);
  glLineWidth(1.0);
  glLineStipple(1, 0x1111);

  glBegin(GL_LINE_LOOP);
  for(v = vertices.begin(); v != vertices.end(); v++) {
    glVertex2d(x + (*v)->x, y + (*v)->y);
  }
  glEnd();
}

void Poly::Move(int mx, int my) {
  x += mx;
  y += my;
}

void Poly::Move(int mx, int my, std::list<Poly *> * polys) {
  int l = len(0, 0, mx, my);
  int k = l;
  int ox = mx;
  int oy = my;

  while(k > 0 && IsColliding(mx, my, polys)) {
    k--;
    mx = (ox * k) / l;
    my = (oy * k) / l;
  }

  Move(mx, my);
}

void Poly::SetPos(int x, int y) {
  this->x = x;
  this->y = y;
}

void Poly::GetPos(int &x, int &y) {
  x = this->x;
  y = this->y;
}

bool Poly::Inside(int px, int py, int mx, int my) {
  // Draw a horizontal line from (px, py) out to 
  // (bx1 + x - 1, py).  If this line intersects an odd number
  // of lines, then the point is inside the polygon.
  unsigned int i;
  int x1, y1, x2, y2, ix, iy;
  int intersects = 0;
  for(i = 0; i < vertices.size(); i++) {
    GetSide(i, x1, y1, x2, y2);
    if(y2 + my != py && 
       line_intersect(x1 + mx, y1 + my, x2 + mx, y2 + my, px, py, 
		      bx1 + x - 1, py, ix, iy)) {
      intersects++;
      cout << py << " " << y1 + my << " " << y2 + my << " / ";
      }
  }
  
  cout << intersects << "\n";
  
  if(intersects % 2) return true;
  return false;
} 

bool line_intersect(int x1, int y1, int x2, int y2,
		    int X1, int Y1, int X2, int Y2, 
		    int &x, int &y) {
  float a, b, A, B, xf, yf;

  if(min(x1, x2) > max(X1, X2) || max(x1, x2) < min(X1, X2) ||
     min(y1, y2) > max(Y1, Y2) || max(y1, y2) < min(Y1, Y2))
     return false;
  
  /*
  cout << x1 << " " << y1 << " "
       << x2 << " " << y2 << ", "
       << X1 << " " << Y1 << " "
       << X2 << " " << Y2;
  */

  if(x1 != x2 && X1 != X2) {
    // Get both lines into 'y = a + bx' format

    //cout << "  n\n";
    b = (float) (y2 - y1) / (float) (x2 - x1);
    a = (float) y1 - b * (float) x1;
    
    B = (float) (Y2 - Y1) / (float) (X2 - X1);
    A = (float) Y1 - B * (float) X1;

    // Catch parallel lines
    if(b == B) return false;

    xf = -(a - A) / (b - B);
    yf = a + b * xf;

    x = (int) xf;
    y = (int) yf;
    
    /*
    cout << "  [" << x << ", " << y << "] "
	 << min(x1, x2) << " " << (x >= min(x1, x2)) << ", "
	 << max(x1, x2) << " " << (x <= max(x1, x2)) << ", "
	 << min(X1, X2) << " " << (x >= min(X1, X2)) << ", "
	 << max(X1, X2) << " " << (x <= max(X1, X2)) << "\n";
    */
    
    if(x >= min(x1, x2) && x <= max(x1, x2) &&
       x >= min(X1, X2) && x <= max(X1, X2) && 
       y >= min(y1, y2) && y <= max(y1, y2) &&
       y >= min(Y1, Y2) && y <= max(Y1, Y2)) {

      /*
      cout << "  intersect at "
	   << x << " " << y 
	   << "(" << b << "," << B << ")\n";
      */

      return true;
    }
  } else if(x1 == x2 && X1 != X2) {
    //cout << "  v1\n";
    // Line 1 is vertical
    B = (float) (Y2 - Y1) / (float) (X2 - X1);
    A = Y1 - B * X1;

    x = x1;
    y = (int) (A + ((float) B * x));
      
    if(y >= min(y1, y2) && y <= max(y1, y2) &&
       x >= min(X1, X2) && x <= max(X1, X2)) {

      /*
      cout << "  intersect at "
	   << x << " " << y << "(v1)\n";
      */
      
      return true;
    }
  } else if(x1 != x2 && X1 == X2) {
    //cout << "  v2\n";
   // Line 2 is vertical
    b = (float) (y2 - y1) / (float) (x2 - x1);
    a = y1 - b * x1;

    x = X1;
    y = (int) (a + ((float)b * x));

    if(x >= min(x1, x2) && x <= max(x1, x2) &&
       y >= min(Y1, Y2) && y <= max(Y1, Y2)) {
      
      /*
      cout << "  intersect at "
	   << x << " " << y << "(v2)\n";
      */
      
      return true;
    }
  } else {
    //cout << "  v1&2\n";
  }

  // If we get here, both lines are vertical.
  return false;
}
