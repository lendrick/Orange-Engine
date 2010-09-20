#ifdef WIN32
#include <windows.h>
#endif

#include "tileselect.h"
#include "bitmap.h"
#include "globals.h"

#include <qwidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qsizepolicy.h>
#include <qgl.h>
#include <iostream>

#include "scrollbar.h"

using std::cout;

TileBox::TileBox(QWidget * parent) :
  QGLWidget(parent, mainGLWidget) {
  tileset = 0;
  selected = 0;
  scroll = 0;
  setMinimumWidth(200);
}

void TileBox::setTileset(Bitmap * t) {
  makeCurrent();
  tileset = t;
  resizeGL(width(), height());
  updateGL();
}

void TileBox::initializeGL() {
  glClearColor( 0.5, 0.5, 0.5, 1.0 ); 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glShadeModel(GL_FLAT);
  //tileset = new Bitmap("town2.png", 16, 16, 0, 0);
}

void TileBox::resizeGL(int w, int h) {
	if(w > 0 && h > 0) {
    //glPushMatrix();
    int vrows, rows, cols;
    int sw, sh;

    //glViewport(0, 0, w, h);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //gluOrtho2D(0, w, h, 0);

    if(tileset) {
      tileset->getSize(sw, sh);
      cols = (width() - 1) / (sw + 1);
      rows = tileset->tileCount() / cols + 1;
      vrows = height() / (sh + 1) + 1;
      
      if(vrows < rows) {
        emit setRange(0, rows-vrows+1);
      } else {
        emit setRange(0, 0);
      }
    } else {
      emit setRange(0, 0);
    }    
    //glPopMatrix();
  }
}

void TileBox::paintGL() {
  glPushMatrix();
  glClearColor( 0.5, 0.5, 0.5, 0.0 ); 
  glClear(GL_COLOR_BUFFER_BIT);
  glViewport(0, 0, width(), height());
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, width(), height(), 0);
  if(tileset) {
    int w, h;
    int x, y, t, rows, cols, tiles;
    tileset->getSize(w, h);
    tiles = tileset->tileCount();
    cols = (this->width() - 1) / (w + 1);
    if(cols == 0) cols = 1;

    rows = (this->height()) / (w + 1) + 1;

    // Draw tiles
    for(y = 0; y < rows; y++) {
      for(x = 0; x < cols; x++) {
	      t = (y + scroll) * cols + x;
	      //cout << y << " " << x << " " << t << "\n";
	      if(t < tiles) tileset->draw(t, x * (w + 1) + 1, y * (h + 1) + 1);
      }
    }
    //cout << "\n";
    
    // Draw select box
    x = (selected % cols) * (w + 1);
    y = (selected / cols - scroll) * (h + 1);
    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0, 1.0, 0.0);

    if(y >= 0) {
      glBegin(GL_LINE_LOOP);
      glVertex3f(x, y + 1, 0);
      glVertex3f(x + w + 1, y + 1, 0);
      glVertex3f(x + w + 1, y + h + 2, 0);
      glVertex3f(x, y + h + 2, 0);   
      glEnd();    
    }
  }
  glFlush();
  glPopMatrix();
}

void TileBox::setSelected(int s) {
  selected = s;
  updateGL();
}

void TileBox::setScroll(int s) {
  makeCurrent();
  scroll = s;
  updateGL();
}

int TileBox::getSelected() {
  return selected;
}

void TileBox::mousePressEvent(QMouseEvent * e) {
  if(tileset) {
    int tx, ty, tile;
    int w, h;
    tileset->getSize(w, h);
    
    tx = e->x() / (w + 1);
    ty = e->y() / (h + 1) + scroll;
    
    tile = tx + ty * (this->width() - this->width() % (w + 1))/ (w + 1);
    if(tile < tileset->tileCount()) selected = tile;

    makeCurrent();
    updateGL();
    //cout << "Selected tile " << selected << "\n";
    emit tileChanged(selected);
    //cout << "Selected tile " << selected << "\n";
  }
}

TileSelect::TileSelect(QWidget *parent) 
  : QWidget(parent) {
  QHBoxLayout * HBox = new QHBoxLayout(this);
  HBox->setContentsMargins(2, 2, 2, 2);
  tilebox = new TileBox(this);
  scroll = new ScrollBar(Qt::Vertical, this);
  scroll->setMaximum(1000);
  scroll->setMinimum(0);

  HBox->addWidget(tilebox);
  HBox->addWidget(scroll);

  connect(scroll, SIGNAL(valueChanged(int)), 
	  tilebox, SLOT(SetScroll(int)));
  connect(tilebox, SIGNAL(SetRange(int, int)), 
	  scroll, SLOT(setRange(int, int)));
}

void TileSelect::setTileset(Bitmap * t) {
  tilebox->setTileset(t);
}

int TileSelect::getTile() {
  return tilebox->getSelected();
}

void TileSelect::setTiles(int t) {
  if(t >= 0) 
    setTileset(bitmaps[t]);
  else
    setTileset((Bitmap *) 0);
}