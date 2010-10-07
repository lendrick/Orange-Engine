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
  tileSpacing = 2;
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
      cols = (width() - 1) / (sw + tileSpacing);
      rows = tileset->tileCount() / cols + 1;
      vrows = height() / (sh + tileSpacing) + 1;
      
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
    int pw, ph;
    int x, y, t, rows, cols, tiles;
    tileset->getSize(w, h);
    tileset->getPixmapSize(pw, ph);
    tiles = tileset->tileCount();
    //cols = (this->width() - 1) / (w + 1);
    tileset->getGridSize(cols, rows);
    if(cols == 0) cols = 1;
    if(rows == 0) rows = 1;

    // Draw tiles
    for(y = 0; y < rows; y++) {
      for(x = 0; x < cols; x++) {
        t = (y + scroll) * cols + x + 1;
        //cout << y << " " << x << " " << t << "\n";
        if(t < tiles)
          tileset->draw(t, x * (w + tileSpacing) + 1,
                        y * (h + tileSpacing) + tileSpacing * 2 + h);
      }
    }
    //cout << "\n";
    
    // Draw select box
    if(selected == 0) {
      x = 0;
      y = 0;
    } else {
      int s = selected - 1;
      x = (s % cols) * (w + tileSpacing);
      y = (s / cols - scroll) * (h + tileSpacing) + h + tileSpacing;
    }

    glDisable(GL_TEXTURE_2D);
    glColor3f(0.8, 0.8, 0.8);
    glLineWidth(2);

    if(y >= 0) {
      glBegin(GL_LINE_LOOP);
      glVertex3f(x, y + 1, 0);
      glVertex3f(x + w + 2, y + 1, 0);
      glVertex3f(x + w + 2, y + h + 3, 0);
      glVertex3f(x, y + h + 3, 0);
      glEnd();    
    }

    glLineWidth(1);
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
    int gw, gh;

    int mx = e->x();
    int my = e->y() + scroll;

    tileset->getSize(w, h);
    tileset->getGridSize(gw, gh);

    if(mx > (gw + tileSpacing) * w || my > (gh + tileSpacing + 1) * h) {
      //qDebug() << "mouse press out of range";
      return;
    }

    qDebug() << ":" << mx << ", " << my << "  " << gw << ", " << gh << " " << tileSpacing;

    if(my < h + tileSpacing) {
      selected = 0;
    } else {
      tx = e->x() / (w + tileSpacing);
      ty = e->y() / (h + tileSpacing);
      ty -= 1;

      tile = tx + ty * gw + 1;
      if(tile < tileset->tileCount()) selected = tile;
    }

    makeCurrent();
    updateGL();
    qDebug() << "Selected tile " << selected << "\n";
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
          tilebox, SLOT(setScroll(int)));
  connect(tilebox, SIGNAL(setRange(int, int)),
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
