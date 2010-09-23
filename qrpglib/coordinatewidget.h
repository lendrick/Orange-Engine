#ifndef COORDINATEWIDGET_H
#define COORDINATEWIDGET_H

#include <QtGui>

class CoordinateWidget : public QFrame {
  Q_OBJECT
public:
  CoordinateWidget(QWidget * parent = 0, int nx = 0, int ny = 0);
  QSpinBox * x;
  QSpinBox * y;
};


#endif // COORDINATEWIDGET_H
