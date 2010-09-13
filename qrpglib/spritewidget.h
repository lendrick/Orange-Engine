#ifndef SPRITEWIDGET_H
#define SPRITEWIDGET_H 1

#ifdef WIN32
#include <windows.h>
#endif
#include <qgl.h>
#include <qtimer.h>
#include "sprite.h"

class SpriteWidget : public QGLWidget {
  Q_OBJECT
public:
  enum Mode {
    PLAY,
    PAUSE,
    FRAME
  };

  SpriteWidget(QWidget * parent=0);
  void SetSprite(Sprite * s);
  Sprite * sprite;
public slots:
  void Play();
  void Pause();
  void Stop();
  void SetState(int);
  void SetFrame(int);
  void updateDuration(int);
signals:
  void SetStateRange(int, int);
  void SetFrameRange(int, int);
  void SetFrameDuration(int);
  void SetSelectedTile(int);
  void updateTime(int);
private:
  void initializeGL();
  void resizeGL(int w, int h);
  void paintGL();
  //void mousePressEvent(QMouseEvent * e);
  void UpdateSpinners();
  
  Mode mode;
  int time_since_start;
  int last_time;

  int state;
  int frame;
  int duration;
  int sw;
  int sh;

  QTimer * timer;
  QTime spriteTime;
};


#endif
