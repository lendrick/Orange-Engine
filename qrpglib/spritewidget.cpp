#ifdef WIN32
#include <windows.h>
#endif

#include "spritewidget.h"
#include "sprite.h"
#include "globals.h"

#include <qgl.h>
#include <qdatetime.h>
#include <qfiledialog.h>
#include <iostream>

using std::cout;
extern QTime apptime;

SpriteWidget::SpriteWidget(QWidget * parent) :
  QGLWidget(parent, mainGLWidget) {
  time_since_start = 0;
  last_time = 0;

  state = 0;
  frame = 0;
  sprite = 0;
  duration = 0;
  sw = 0;
  sh = 0;

  mode = FRAME;

  spriteTime.start();

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
  timer->stop();
}

void SpriteWidget::setSprite(Sprite * s) {
  sprite = s;
  spriteTime.restart();
  if(sprite && sprite->getTileset())
    sprite->getTileset()->getSize(sw, sh);
  updateGL();
}

void SpriteWidget::initializeGL() {
  glClearColor( 0.5, 0.5, 0.5, 1.0 ); 
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glShadeModel(GL_FLAT);
}

void SpriteWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(0, w, h, 0);
}

void SpriteWidget::paintGL() {
  glClearColor( 0.5, 0.5, 0.5, 0.0 ); 
  glClear(GL_COLOR_BUFFER_BIT);
  int x = (width() - sw) / 2;
  int y = (height() - sh) / 2;

  if(sprite) {
    if(mode == FRAME) {
      sprite->drawFrame(state, frame, x, y);
    } else {
      sprite->draw(state, spriteTime.elapsed(), x, y);
      if(duration)
        updateTime(spriteTime.elapsed() % duration);
      else
        updateTime(spriteTime.elapsed());
    }
  }
  glFlush();
}

void SpriteWidget::play() {
  mode = PLAY;
  timer->start(1000 / 30);
  spriteTime.restart();
}

void SpriteWidget::stop() {
  mode = FRAME;
  timer->stop();
  updateGL();
}

void SpriteWidget::pause() {
  mode = PAUSE;
  timer->stop();
  updateGL();
}

void SpriteWidget::setState(int s) {
  state = s;
  frame = 0;
  spriteTime.restart();
  updateGL();
}

void SpriteWidget::setFrame(int f) {
  frame = f;
  updateGL();
}

//void SpriteWidget::mousePressEvent(QMouseEvent * e) {
//}

void SpriteWidget::updateDuration(int time) {
  duration = time;
}