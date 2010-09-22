#ifndef TALKBOX_H
#define TALKBOX_H 1

#include <QtGui>
#include "imageframe.h"

class TalkBox;

class TalkBoxProxy : public QGraphicsProxyWidget {
  Q_OBJECT
public:
  TalkBoxProxy(QString text, QGraphicsItem * parent = 0);
private:
  TalkBox * widget;
};

class TalkBox : public QTextEdit {
  Q_OBJECT
public:
  TalkBox(QString text, QGraphicsProxyWidget * p);
  ~TalkBox();
  void say(QString s);
protected:
  //virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
  QGraphicsProxyWidget * proxy;
  void showEvent(QShowEvent * e);
  void mousePressEvent(QMouseEvent *e);
  void mouseDoubleClickEvent(QMouseEvent *e);
  void mouseMoveEvent(QMouseEvent *e);
  void enterEvent(QEvent * e);
  void leaveEvent(QEvent * e);
  void keyPressEvent(QKeyEvent *e);
  void focusOutEvent(QFocusEvent *e);
public slots:
  void pageDown();
  void next();
signals:
  void start();
private:
  int lineHeight;
};

#endif
