#ifndef TALKBOX_H
#define TALKBOX_H 1

#include <QtGui>
#include "imageframe.h"

class TalkBox : public QTextEdit {
  Q_OBJECT
public:
  TalkBox(QString text, QGraphicsItem * parent = 0);
  void say(QString s);
protected:
  //virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
  QGraphicsProxyWidget * proxy;
  void showEvent(QShowEvent * e);
public slots:
  void next();
signals:
  void start();
};

#endif
