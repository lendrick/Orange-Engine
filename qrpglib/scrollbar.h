#ifndef SCROLLBAR_H
#define SCROLLBAR_H 1

#include <qscrollbar.h>

class ScrollBar : public QScrollBar {
  Q_OBJECT
public:
  ScrollBar(QWidget * parent = 0) :
    QScrollBar(parent) {};
  ScrollBar(Qt::Orientation orientation, QWidget * parent = 0) :
    QScrollBar(orientation, parent) {};
public slots:
  void setRange(int, int);
};

#endif
